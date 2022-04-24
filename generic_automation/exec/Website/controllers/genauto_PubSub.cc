#include "genauto_PubSub.h"
#include "Log.hpp"
#include "HexStringSerializer.hpp"
#include "../files/Common.h"
#include "Capabilities.hpp"
#include "../database/Database.hpp"
#include "../files/DeviceSubscribeManager.hpp"
#include "../lib/Common/include/Timer.hpp"

#include <arpa/inet.h>

using namespace genauto;
//add definition of your processing function here


void PubSub::handle(const HttpRequestPtr &req,
                    std::function<void (const HttpResponsePtr &)> &&callback,
                    const std::string& data)
{
    HexStringSerializer serializer(1000);
    uint8_t buffer[1000];
    LOG_DEBUG << "Got " << data << "\n";
    serializer.parse((uint8_t*)data.c_str(), data.size());
    Message msg(buffer, sizeof(buffer));
    if (serializer.deserialize(&msg) != HexStringSerializer::Success) {
        elog("Error occurred while parsing\n");
        callback(HttpResponse::newHttpResponse());
        return;
    }

    if (msg.type() == CapabilitiesMessage::classMsgType) {
        CapabilitiesMessage real(msg.getBuffer(), msg.getBufferSize());
        real.log();
        std::string devId;
        dlog("Got mac = %s\n", real.mac());
        auto resp=HttpResponse::newHttpResponse();
        resp->setStatusCode(k200OK);
        resp->setContentTypeCode(CT_TEXT_HTML);
        bool found = false;
        for (auto& el : JsonFile::deviceIds.j.items()) {
            if (!el.value().is_object()) {
                continue;
            }
            if (el.value()["mac"].get<std::string>() == real.mac()) {
                found = true;
                devId = el.key();
                resp->setBody(devId);
            }
        }
        if (!found) {
            int max = 1;
            for (auto& el : JsonFile::deviceIds.j.items()) {
                int key = std::stoi(el.key());
                dlog("Checking %d\n", key);
                if (key > max) {
                    max = key;
                }
            }
            devId = std::to_string(max + 1);
            JsonFile::deviceIds.j[devId]["mac"] = real.mac();

        }
        resp->setBody(devId);
        callback(resp);

        in_addr ip;
        ip.s_addr = real.ip();
        JsonFile::deviceIds.j[devId]["ip"] = inet_ntoa(ip);
        JsonFile::deviceIds.save();

        if (DevicesDatabase::exists(devId)) {
            dlog("Updating dev %s\n", devId.c_str());
            DevicesDatabase::update(&real, devId);
        } else {
            dlog("Generating dev %s\n", devId.c_str());
            DevicesDatabase::generate(&real, devId);
        }


        callAsync(
            [devId](void) {
                Timer::delay(3000);
                for (auto& output : DevicesDatabase::deviceBase.data.j[devId]["outputs"].items()) {
                    for(auto& linked : output.value()["persistent"]["linked"].items()) {
                        major_t maj = std::stoi(devId);
                        minor_t min = std::stoi(output.key());
                        MessageId id(maj,min);
                        MessageId other(linked.value().get<std::string>().c_str());
                        DeviceSubscribeManager::addSub(id, other);
                    }
                }
            }
        );
        return;
    }
    callback(HttpResponse::newHttpResponse());
}

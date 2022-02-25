#include "genauto_PubSub.h"
#include "Log.hpp"
#include "HexStringSerializer.hpp"
#include "Capabilities.hpp"
#include "../database/Database.hpp"

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
        CapabilitiesMessage real(msg);
        real.log();
        std::string devId;
        dlog("Got mac = %s\n", real.mac());
        auto resp=HttpResponse::newHttpResponse();
        resp->setStatusCode(k200OK);
        resp->setContentTypeCode(CT_TEXT_HTML);
        if (JsonFile::deviceIds.j.contains(real.mac())) {
            devId = JsonFile::deviceIds.j[real.mac()];
            resp->setBody(devId);
        } else {
            int max = 1;
            for (auto& el : JsonFile::deviceIds.j.items()) {
                int key = std::stoi(el.key());
                if (key > max) {
                    key = max;
                }
            }
            devId = std::to_string(max + 1);
            JsonFile::deviceIds.j[real.mac()] = std::to_string(max + 1);
            JsonFile::deviceIds.save();
        }
        resp->setBody(devId);
        callback(resp);

        if (DevicesDatabase::exists(devId)) {
            dlog("Updating dev %s\n", devId.c_str());
            DevicesDatabase::update(&real, devId);
        } else {
            dlog("Generating dev %s\n", devId.c_str());
            DevicesDatabase::generate(&real, devId);
        }
    }
    callback(HttpResponse::newHttpResponse());
}
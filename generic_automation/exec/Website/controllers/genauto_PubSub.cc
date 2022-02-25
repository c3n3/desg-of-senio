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
        dlog("Got mac = %s\n", real.mac());
        auto resp=HttpResponse::newHttpResponse();
        resp->setStatusCode(k200OK);
        resp->setContentTypeCode(CT_TEXT_HTML);
        if (JsonFile::deviceIds.j.contains(real.mac())) {
            std::string id = JsonFile::deviceIds.j[real.mac()];
            resp->setBody(id);
            if (DevicesDatabase::exists(id)) {
                DevicesDatabase::update(&real, id);
            }
        } else {
            int max = 1;
            for (auto& el : JsonFile::deviceIds.j.items()) {
                int key = std::stoi(el.key());
                if (key > max) {
                    key = max;
                }
            }
            resp->setBody(std::to_string(max + 1));
            JsonFile::deviceIds.j[real.mac()] = std::to_string(max + 1);
            JsonFile::deviceIds.save();
        }
        callback(resp);
    }
    callback(HttpResponse::newHttpResponse());
}
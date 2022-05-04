#include "genauto_pages_Devices.h"
#include "Types.hpp"
#include "Message.hpp"
#include "EncoderMessage.hpp"
#include "ButtonMessage.hpp"
#include "HexStringSerializer.hpp"
#include "../database/Database.hpp"
#include "../json/json.hpp"
#include <drogon/HttpClient.h>
#include "../files/Common.h"

using namespace genauto::pages;
using json = nlohmann::json;

Devices::Devices() : serializer(1000)
{}

void Devices::mainFun(
    const HttpRequestPtr &req,
    std::function<void (const HttpResponsePtr &)> &&callback)
{
    LOG_DEBUG << "Main webpage accessed\n";
    auto para=req->getParameters();
    HttpViewData data;
    std::string database;
    
    DevicesDatabase::deviceBase.htmlOutput(database);
    data.insert("json", database);
    auto resp=HttpResponse::newHttpViewResponse("Devices.csp", data);
    callback(resp);
}

void Devices::update(const HttpRequestPtr &req,
                    std::function<void (const HttpResponsePtr &)> &&callback,
                    const std::string& data,
                    const std::string& keystring,
                    const std::string& type)
{
    LOG_INFO << "------------------ CALLED --------------------\n";
    json parsed = json::parse(data);
    DevicesDatabase::deviceBase.update(keystring, type, parsed);
    callback(HttpResponse::newHttpResponse());
}


void Devices::encoderSend(const HttpRequestPtr &req,
    std::function<void (const HttpResponsePtr &)> &&callback,
    const major_t& major,
    const uint32_t& minor,
    const int16_t& inc)
{
    EncoderMessage m;
    m.id().major = major;
    m.id().minor = minor;
    m.value() = inc;
    dlog("increment = %d\n", inc);
    genauto::sendTo(&m);
    callback(HttpResponse::newHttpResponse());
}

void Devices::buttonSend(const HttpRequestPtr &req,
    std::function<void (const HttpResponsePtr &)> &&callback,
    const major_t& major,
    const uint32_t& minor,
    const bool& on)
{
    ButtonMessage m;
    m.id().major = major;
    m.id().minor = minor;
    m.pressed() = true;
    dlog("Sending: type 0x%x\n", m.type());
    genauto::sendTo(&m);
    dlog("Tried to SEND BUTTON\n");
    callback(HttpResponse::newHttpResponse());
}

#include "genauto_pages_Devices.h"
#include "Types.hpp"
#include "Message.hpp"
#include "EncoderMessage.hpp"
#include "HexStringSerializer.hpp"
#include "../database/Database.hpp"
#include "../json/json.hpp"

#include <drogon/HttpClient.h>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>

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
    auto resp=HttpResponse::newHttpViewResponse("Devices.csp",data);
    callback(resp);
}

void Devices::update(const HttpRequestPtr &req,
                    std::function<void (const HttpResponsePtr &)> &&callback,
                    const std::string& data,
                    const std::string& keystring,
                    const std::string& type)
{
    json parsed = json::parse(data);
    DevicesDatabase::deviceBase.update(keystring, type, parsed);
}

static HexStringSerializer serializer(1000);

template <class F>
void call_async(F&& fun) {
    auto futptr = std::make_shared<std::future<void>>();
    *futptr = std::async(std::launch::async, [futptr, fun]() {
        fun();
    });
}



static void send(Message* message)
{
    std::string id = std::to_string(message->id().getMajor());
    if (!JsonFile::deviceIds.j.contains(id)) {
        elog("Invalid id %s\n", id.c_str());
        return;
    }
    std::string ip = JsonFile::deviceIds.j[id]["ip"];

    // Set as sending to
    message->id().to();

    std::string willSend = std::string("http://") + ip + std::string("?d=") + serializer.getBuffer();
    serializer.serialize(message);
    std::cout << willSend << "\n";
    std::ostringstream os;
    os << curlpp::options::Url(willSend);
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
    send(&m);
    dlog("DONE\n");
    callback(HttpResponse::newHttpResponse());
    // void send(Message* message)
    // std::ostringstream os;
    // serilizer.serialize(message);
    // std::string willSend = std::string("http://10.150.148.214?d=") + serilizer.getBuffer();
    // std::cout << willSend << "\n";
    // os << curlpp::options::Url(willSend);
}

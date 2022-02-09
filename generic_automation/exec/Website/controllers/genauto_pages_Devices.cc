#include "genauto_pages_Devices.h"
#include "Types.hpp"
#include "Message.hpp"
#include "EncoderMessage.hpp"
#include "HexStringSerializer.hpp"
#include <drogon/HttpClient.h>
#include "../json/json.hpp"

#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>

using namespace genauto::pages;
using json = nlohmann::json;

Devices::Devices() : base("../database/devices.json"), serializer(1000)
{}

void Devices::mainFun(
    const HttpRequestPtr &req,
    std::function<void (const HttpResponsePtr &)> &&callback)
{
    LOG_DEBUG << "Main webpage accessed\n";
    auto para=req->getParameters();
    HttpViewData data;
    std::string database;
    
    base.htmlOutput(database);
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
    base.update(keystring, type, parsed);
    base.save();
}

void Devices::deviceComm(const HttpRequestPtr &req,
    std::function<void (const HttpResponsePtr &)> &&callback,
    const std::string& data)
{
    callback(HttpResponse::newHttpResponse());
    uint8_t massiveBuffer[100];
    Message msg(massiveBuffer);
    LOG_DEBUG << "Called!";
    if (serializer.parse((uint8_t*)data.c_str(), data.length()) == HexStringSerializer::Success) {
        if (serializer.deserialize(msg) == HexStringSerializer::Success) {
            msg.log();
        }
    }

    
    // auto client = HttpClient::newHttpClient(
    //     "http://10.150.148.214",80);
	// auto newReq = HttpRequest::newHttpRequest();
	// std::promise<bool> valid;
	// req->setPath("/?test=ASDLKJFSD");
    // LOG_DEBUG << "Called!";
	// client->sendRequest(newReq, [&](ReqResult result, const HttpResponsePtr &response) {
    // LOG_DEBUG << "Called!";
	// 	if(response == nullptr) // If no server responce
	// 		valid.set_value(false);
	// 	valid.set_value(true);
    // LOG_DEBUG << "Called!";
	// });
	// bool api_ok = valid.get_future().get(); // Wait for HTTP to response. Have to wait here otherwise crash the entire application

    // LOG_DEBUG << "Called!";
    // callback(HttpResponse::newHttpResponse());
    // LOG_DEBUG << "Called!";
}

static HexStringSerializer serializer(1000);

static void send(Message* message)
{
    std::ostringstream os;
    serializer.serialize(message);
    std::string willSend = std::string("http://172.20.10.11?d=") + serializer.getBuffer();
    std::cout << willSend << "\n";
    os << curlpp::options::Url(willSend);
}



void Devices::encoderSend(const HttpRequestPtr &req,
    std::function<void (const HttpResponsePtr &)> &&callback,
    const major_t& major,
    const minor_t& minor,
    const int16_t& inc)
{
    callback(HttpResponse::newHttpResponse());
    EncoderMessage m;
    dlog("Inc: %d\n", inc);
    m.id() = MessageId(major,minor);
    m.value() = inc;
    m.log();
    send(&m);
    // void send(Message* message)
    // std::ostringstream os;
    // serilizer.serialize(message);
    // std::string willSend = std::string("http://10.150.148.214?d=") + serilizer.getBuffer();
    // std::cout << willSend << "\n";
    // os << curlpp::options::Url(willSend);
}

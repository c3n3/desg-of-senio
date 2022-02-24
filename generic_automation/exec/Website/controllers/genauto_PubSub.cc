#include "genauto_PubSub.h"
#include "Log.hpp"
#include "HexStringSerializer.hpp"
using namespace genauto;
//add definition of your processing function here


void PubSub::handle(const HttpRequestPtr &req,
                    std::function<void (const HttpResponsePtr &)> &&callback,
                    const std::string& data)
{
    HexStringSerializer serializer(1000);
    uint8_t buffer[1000];
    callback(HttpResponse::newHttpResponse());
    LOG_DEBUG << "Got " << data << "\n";
    serializer.parse((uint8_t*)data.c_str(), data.size());
    Message msg(buffer, sizeof(buffer));
    serializer.deserialize(&msg);
    msg.log();
}
#include "genauto_PubSub.h"
#include "Log.hpp"
using namespace genauto;
//add definition of your processing function here



void PubSub::handle(const HttpRequestPtr &req,
                    std::function<void (const HttpResponsePtr &)> &&callback,
                    const std::string& data)
{
    callback(HttpResponse::newHttpResponse());
    LOG_DEBUG << "Got " << data << "\n";
}
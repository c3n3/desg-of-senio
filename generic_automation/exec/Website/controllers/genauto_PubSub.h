#pragma once
#include <drogon/HttpController.h>
using namespace drogon;
namespace genauto
{
class PubSub:public drogon::HttpController<PubSub>
{
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(PubSub::handle,"/_ps_?d={}",Get);
    METHOD_LIST_END
    void handle(const HttpRequestPtr &req,
                    std::function<void (const HttpResponsePtr &)> &&callback,
                    const std::string& data);
};
}

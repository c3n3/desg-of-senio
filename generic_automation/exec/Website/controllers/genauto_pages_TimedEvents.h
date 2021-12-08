#pragma once
#include <drogon/HttpController.h>
using namespace drogon;
namespace genauto
{
namespace pages
{
class TimedEvents:public drogon::HttpController<TimedEvents>
{
  public:
    METHOD_LIST_BEGIN
      METHOD_ADD(TimedEvents::mainFun, "", Get);
    METHOD_LIST_END

    void mainFun(const HttpRequestPtr &req,
                       std::function<void (const HttpResponsePtr &)> &&callback);
};
}
}

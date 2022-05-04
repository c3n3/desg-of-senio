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
      METHOD_ADD(TimedEvents::save, "/save?data={}", Post);
    METHOD_LIST_END

    void mainFun(const HttpRequestPtr &req,
                       std::function<void (const HttpResponsePtr &)> &&callback);

    void save(const HttpRequestPtr &req,
          std::function<void (const HttpResponsePtr &)> &&callback,
          const std::string& data);

};
}
}

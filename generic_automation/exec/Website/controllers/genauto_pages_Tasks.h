#pragma once
#include <drogon/HttpController.h>
using namespace drogon;
namespace genauto
{
namespace pages
{
class Tasks:public drogon::HttpController<Tasks>
{
  public:
    METHOD_LIST_BEGIN
      METHOD_ADD(Tasks::mainFun, "", Get);
    METHOD_LIST_END

    void mainFun(const HttpRequestPtr &req,
                       std::function<void (const HttpResponsePtr &)> &&callback);
};
}
}

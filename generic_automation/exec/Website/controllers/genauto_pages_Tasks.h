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
      METHOD_ADD(Tasks::save, "/save?data={}", Post);
      METHOD_ADD(Tasks::run, "/run?data={}", Post);
      METHOD_ADD(Tasks::stop, "/stop?data={}", Post);
    METHOD_LIST_END

    void mainFun(const HttpRequestPtr &req,
          std::function<void (const HttpResponsePtr &)> &&callback);

    void save(const HttpRequestPtr &req,
          std::function<void (const HttpResponsePtr &)> &&callback,
          const std::string& data);

    void run(const HttpRequestPtr &req,
          std::function<void (const HttpResponsePtr &)> &&callback,
          const std::string& data);

    void stop(const HttpRequestPtr &req,
          std::function<void (const HttpResponsePtr &)> &&callback,
          const std::string& data);
};
}
}

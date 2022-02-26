#pragma once
#include "HexStringSerializer.hpp"
#include <drogon/HttpController.h>
#include "../database/Database.hpp"
using namespace drogon;
namespace genauto
{
namespace pages
{
class Devices:public drogon::HttpController<Devices>
{
  public:
    Devices();
    METHOD_LIST_BEGIN
      METHOD_ADD(Devices::mainFun, "", Get);
      METHOD_ADD(Devices::update, "/update?data={}&keystring={}&type={}", Post);
      METHOD_ADD(Devices::encoderSend, "/encoder_send?major={}&minor={}&inc={}", Post);
    METHOD_LIST_END

    void mainFun(const HttpRequestPtr &req,
                       std::function<void (const HttpResponsePtr &)> &&callback);

    void update(const HttpRequestPtr &req,
                    std::function<void (const HttpResponsePtr &)> &&callback,
                    const std::string& data,
                    const std::string& keystring,
                    const std::string& type);

    void encoderSend(const HttpRequestPtr &req,
                    std::function<void (const HttpResponsePtr &)> &&callback,
                    const major_t& major,
                    const minor_t& minor,
                    const int16_t& inc);

    HexStringSerializer serializer;
};
}
}
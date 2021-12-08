#pragma once
#include <drogon/HttpController.h>
using namespace drogon;
namespace genauto
{
namespace pages
{
class Devices:public drogon::HttpController<Devices>
{
  public:
    METHOD_LIST_BEGIN
      METHOD_ADD(Devices::mainFun, "", Get);
    METHOD_LIST_END

    void mainFun(const HttpRequestPtr &req,
                       std::function<void (const HttpResponsePtr &)> &&callback);
};

class SubDevice {
public:
  const std::string prefix;
  const std::string name;
  const std::string inputType;
  SubDevice(std::string name, std::string action, std::string type);
  virtual std::string getLine() = 0;
};

class Output : public SubDevice {
public:
  std::string getLine();
  Output(std::string name, std::string action, std::string type);
};

class Input : public SubDevice {
public:
  enum Type {
    Value,
    Event
  };
  const Type t;
  Input(std::string name, std::string action, std::string type, Type t);
  std::string getLine();
};

class Device {
public:
  Device(std::string title);
  const std::string title;
  std::vector<Output> outputDevices;
  std::vector<Input> inputDevices;
};

}
}

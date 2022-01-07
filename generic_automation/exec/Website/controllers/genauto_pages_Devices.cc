#include "genauto_pages_Devices.h"
#include <nlohmann/json.hpp>
using namespace genauto::pages;
using json = nlohmann::json;

Devices::Devices() : base("../database/devices.json")
{}

void Devices::mainFun(
    const HttpRequestPtr &req,
    std::function<void (const HttpResponsePtr &)> &&callback)
{
    LOG_DEBUG << "Main webpage accessed\n";
    auto para=req->getParameters();
    HttpViewData data;
    std::vector<Device> devices;
    for (int i = 0; i < 5; i++) {
        Device a(std::string("Device ") + std::to_string(i));
        a.outputDevices.push_back(Output("Motor A", "Move", "number"));
        a.outputDevices.push_back(Output("Motor B", "Move", "number"));
        a.outputDevices.push_back(Output("PWM A", "Set PWM", "number"));

        a.inputDevices.push_back(Input("Analog A", "", "0.25V", Input::Value));
        a.inputDevices.push_back(Input("Analog B", "", "1.2V", Input::Value));
        a.inputDevices.push_back(Input("Button A", "Set", "text", Input::Event));
        a.inputDevices.push_back(Input("Encoder A", "Set", "text", Input::Event));
        devices.push_back(a);
    }
    data.insert("devices", devices);
    auto resp=HttpResponse::newHttpViewResponse("Devices.csp",data);
    callback(resp);
}

SubDevice::SubDevice(std::string name, std::string prefix, std::string type)
    : name(name), prefix(prefix), inputType(type)
{}

std::string Output::getLine()
{
    std::stringstream ss;
    ss << prefix << " " << name;
    return ss.str();
}

Output::Output(std::string name, std::string prefix, std::string type)
: SubDevice(name, prefix, type)
{}

Input::Input(std::string name, std::string prefix, std::string type, Type t)
: SubDevice(name, prefix, type), t(t)
{}

std::string Input::getLine()
{
    std::stringstream ss;
    if (t == Value) {
        ss << prefix << " " << name << ": " << inputType;
    } else if (t == Event) {
        ss << prefix << " " << name;
    }
    return ss.str();
}

Device::Device(std::string title) : title(title)
{}

void Devices::update(const HttpRequestPtr &req,
                    std::function<void (const HttpResponsePtr &)> &&callback,
                    const std::string& data,
                    const std::string& keystring)
{
    json parsed = json::parse(data);
    base.update(keystring, parsed);
    base.save();
}
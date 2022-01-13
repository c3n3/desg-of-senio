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
    std::string database;
    
    base.htmlOutput(database);
    data.insert("json", database);
    auto resp=HttpResponse::newHttpViewResponse("Devices.csp",data);
    callback(resp);
}

void Devices::update(const HttpRequestPtr &req,
                    std::function<void (const HttpResponsePtr &)> &&callback,
                    const std::string& data,
                    const std::string& keystring,
                    const std::string& type)
{
    json parsed = json::parse(data);
    base.update(keystring, type, parsed);
    base.save();
}
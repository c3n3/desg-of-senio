#include "genauto_pages_TimedEvents.h"
#include "../database/Database.hpp"
#include "genauto_pages_Tasks.h"
#include "../files/Common.h"
#include "../json/json.hpp"
#include "../files/Task.hpp"
#include "../files/TimedTask.hpp"

using namespace genauto::pages;
//add definition of your processing function here
void TimedEvents::mainFun(
    const HttpRequestPtr &req,
    std::function<void (const HttpResponsePtr &)> &&callback)
{
    LOG_DEBUG << "Tasks webpage accessed\n";
    auto para=req->getParameters();
    HttpViewData data;
    std::string database;
    database.reserve(5000);
    json output;
    output["tasks"] = JsonFile::tasks.j;
    output["events"] = JsonFile::timedEvents.j;
    genauto::htmlOutput(output, database);
    data.insert("json", database);
    auto resp=HttpResponse::newHttpViewResponse("TimedEvents.csp",data);
    callback(resp);
}


//add definition of your processing function here
void TimedEvents::save(
    const HttpRequestPtr &req,
    std::function<void (const HttpResponsePtr &)> &&callback,
    const std::string& data)
{
    json j;
    j = j.parse(data);
    std::cout << data << "\n";
    JsonFile::timedEvents.j = j;
    JsonFile::timedEvents.save();
    dlog("Saving new info");
    callback(HttpResponse::newHttpResponse());
    // Update the loop
}

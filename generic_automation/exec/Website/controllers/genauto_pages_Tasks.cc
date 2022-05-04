#include "../database/Database.hpp"
#include "genauto_pages_Tasks.h"
#include "../files/Common.h"
#include "../json/json.hpp"
#include "../files/Task.hpp"

using namespace genauto::pages;
//add definition of your processing function here
void Tasks::mainFun(
    const HttpRequestPtr &req,
    std::function<void (const HttpResponsePtr &)> &&callback)
{
    LOG_DEBUG << "Tasks webpage accessed\n";
    auto para=req->getParameters();
    HttpViewData data;
    std::string database;
    database.reserve(5000);
    json output;
    output["devices"] = DevicesDatabase::deviceBase.data.j;
    output["tasks"] = JsonFile::tasks.j;
    genauto::htmlOutput(output, database);
    data.insert("json", database);
    auto resp=HttpResponse::newHttpViewResponse("Tasks.csp", data);
    callback(resp);
}

//add definition of your processing function here
void Tasks::save(
    const HttpRequestPtr &req,
    std::function<void (const HttpResponsePtr &)> &&callback,
    const std::string& data)
{
    json j;
    j = j.parse(data);
    std::cout << data << "\n";
    JsonFile::tasks.j = j;
    JsonFile::tasks.save();
    dlog("Saving new info\n");
    callback(HttpResponse::newHttpResponse());
}

//add definition of your processing function here
void Tasks::run(
    const HttpRequestPtr &req,
    std::function<void (const HttpResponsePtr &)> &&callback,
    const std::string& data)
{
    json j;
    j = j.parse(data);
    callback(HttpResponse::newHttpResponse());
    if (!j.contains("value") || !j.contains("name")) {
        elog("Invalid task\n");
        return;
    }
    if (!Task::running(j["name"])) {

        dlog("Running task\n");
        auto t = new Task(j["value"], j["name"]);
        t->run();
    } else {
        dlog("Task already running\n");
    }
}

//add definition of your processing function here
void Tasks::stop(
    const HttpRequestPtr &req,
    std::function<void (const HttpResponsePtr &)> &&callback,
    const std::string& data)
{
    json j;
    j = j.parse(data);
    callback(HttpResponse::newHttpResponse());
    if (!j.contains("name")) {
        elog("Invalid task\n");
        return;
    }
    if (Task::running(j["name"])) {
        Task::stopTask(j["name"]);
    } else {
        dlog("No task\n");
    }
}

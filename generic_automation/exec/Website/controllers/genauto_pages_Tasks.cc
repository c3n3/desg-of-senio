#include "../database/Database.hpp"
#include "genauto_pages_Tasks.h"
#include "../files/Common.h"
#include "../json/json.hpp"

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
    auto resp=HttpResponse::newHttpViewResponse("Tasks.csp",data);
    callback(resp);
}

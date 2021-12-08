#include "genauto_pages_Tasks.h"
using namespace genauto::pages;
//add definition of your processing function here
void Tasks::mainFun(
    const HttpRequestPtr &req,
    std::function<void (const HttpResponsePtr &)> &&callback)
{
    LOG_DEBUG << "Tasks webpage accessed\n";
    auto para=req->getParameters();
    HttpViewData data;
    auto resp=HttpResponse::newHttpViewResponse("Tasks.csp",data);
    callback(resp);
}

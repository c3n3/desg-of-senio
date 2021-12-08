#include "genauto_pages_TimedEvents.h"
using namespace genauto::pages;
//add definition of your processing function here
void TimedEvents::mainFun(
    const HttpRequestPtr &req,
    std::function<void (const HttpResponsePtr &)> &&callback)
{
    LOG_DEBUG << "Timed events webpage accessed\n";
    auto para=req->getParameters();
    HttpViewData data;
    auto resp=HttpResponse::newHttpViewResponse("TimedEvents.csp",data);
    callback(resp);
}

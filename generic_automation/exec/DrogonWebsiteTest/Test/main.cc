#include <drogon/drogon.h>
#include <drogon/HttpController.h>
using namespace drogon;

int main() {
    //Set HTTP listener address and port
    drogon::app().addListener("0.0.0.0",80);
    //Load config file
    //drogon::app().loadConfigFile("../config.json");
    //Run HTTP framework,the method will block in the internal event loop

    drogon::HttpAppFramework::instance()
        .registerHandler("/list_para",
                        [=](const HttpRequestPtr &req,
                            std::function<void (const HttpResponsePtr &)> &&callback)
                        {
                            auto para=req->getParameters();
                            HttpViewData data;
                            data.insert("title","ListParameters");
                            data.insert("parameters",para);
                            auto resp=HttpResponse::newHttpViewResponse("ListParameters.csp",data);
                            callback(resp);
                        });


    drogon::app().run();
    return 0;
}

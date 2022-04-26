#include <drogon/drogon.h>

#include "files/TimedTask.hpp"
#include <iostream>

int main() {
    //Set HTTP listener address and port
    drogon::app().addListener("0.0.0.0",80);
    //Load config file
    //drogon::app().loadConfigFile("../config.json");
    //Run HTTP framework,the method will block in the internal event loop

    genauto::TimedLoop::init();
    std::cout << "Here\n";
    drogon::app().run();
    return 0;
}

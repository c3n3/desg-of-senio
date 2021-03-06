#include "Common.h"
#include "../database/Database.hpp"
#include "HexStringSerializer.hpp"
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

using namespace genauto;

void genauto::encode(std::string& data)
{
    std::string buffer;
    buffer.reserve(data.size());
    for(size_t pos = 0; pos != data.size(); ++pos) {
        switch(data[pos]) {
            case '&':  buffer.append("&amp;");       break;
            case '\"': buffer.append("&quot;");      break;
            case '\'': buffer.append("&apos;");      break;
            case '<':  buffer.append("&lt;");        break;
            case '>':  buffer.append("&gt;");        break;
            default:   buffer.append(&data[pos], 1); break;
        }
    }
    data.swap(buffer);
}

void genauto::removeNewLines(std::string& data)
{
    for (int i = 0; i < data.length(); i++) {
        if (data[i] == '\n') {
            data[i] = ' ';
        }
    }
}


void genauto::htmlOutput(json& j, std::string& str)
{
    std::stringstream read;
    read << j;
    str = read.str();
    genauto::removeNewLines(str);
}


void genauto::sendTo(Message* message)
{
    static HexStringSerializer serializer(2000);
    std::cout << "Here is the id: " << message->id().major << "\n";
    std::string id = std::to_string(message->id().major);
    if (!JsonFile::deviceIds.j.contains(id)) {
        elog("Invalid id %s\n", id.c_str());
        return;
    }
    std::string ip = JsonFile::deviceIds.j[id]["ip"];

    // Set as sending to
    message->id().to();

    serializer.serialize(message);
    std::string willSend = std::string("http://") + ip + std::string("?d=") + serializer.getBuffer();
    std::cout << "Will send: " << willSend << "\n";
    cURLpp::Easy handle;
    handle.setOpt(curlpp::options::Timeout(5));
    handle.setOpt(curlpp::options::Url(willSend));
    try {
        handle.perform();
    } catch(...) {
        dlog("No route to host\n");
    }
}

void genauto::send(Message* message, major_t device)
{
    static HexStringSerializer serializer(2000);

    std::string id = std::to_string(device);
    if (!JsonFile::deviceIds.j.contains(id)) {
        elog("Invalid id %s\n", id.c_str());
        return;
    }
    std::string ip = JsonFile::deviceIds.j[id]["ip"];

    serializer.serialize(message);
    std::string willSend = std::string("http://") + ip + std::string("?d=") + serializer.getBuffer();
    std::cout << "Will send: " << willSend << "\n";
    cURLpp::Easy handle;
    handle.setOpt(curlpp::options::Url(willSend));
    handle.perform();
}

json genauto::find(std::string name, json& j)
{
    if (!j.is_array()) {
        return json();
    }
    for (auto& el : j.items()) {
        if (el.value()["name"] == name) {
            return el.value();
        }
    }
    return json();
}
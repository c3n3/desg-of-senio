#include "Database.hpp"
#include "../files/Common.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <trantor/utils/Logger.h>
#include "../files/DeviceSubscribeManager.hpp"

using namespace genauto;

DevicesDatabase::DevicesDatabase(const char* fileName) : data(fileName)
{
    data.load();
}


static void updateLinks(const json& oldLinks, const json& newLinks, MessageId id)
{
    // Terribly ineffecient algo, but not important here
    // If not found, we must remove the sub
    for (const auto& el : oldLinks.items()) {
        bool found = false;
        for (const auto& nel : newLinks.items()) {
            if (nel.value() == el.value()) {
                found = true;
            }
        }
        if (!found) {
            MessageId subId(std::string(el.value()).c_str());
            std::string major = std::to_string(subId.major);
            std::string minor = std::to_string(subId.minor);

            DeviceSubscribeManager::removeSub(id, subId);
            found = false;
        }
    }

    // If not found, we must add the sub
    for (const auto& el : newLinks.items()) {
        bool found = false;
        for (const auto& nel : oldLinks.items()) {
            if (nel.value() == el.value()) {
                found = true;
            }
        }
        if (!found) {
            MessageId subId(std::string(el.value()).c_str());
            std::string major = std::to_string(subId.major);
            std::string minor = std::to_string(subId.minor);

            std::cout << "Adding  sub " << major + ":" + minor << " For " << id.major << "\n";
            DeviceSubscribeManager::addSub(id, subId);
            found = false;
        }
    }
}

void DevicesDatabase::update(
    const std::string& keystring, const std::string& type, const json& input)
{
    MessageId dev(keystring.c_str());
    std::string major = std::to_string(dev.major);
    std::string minor = std::to_string(dev.minor);
    auto& persistent = data.j[major][type][minor]["persistent"];
    if (type == "outputs") {
        updateLinks(persistent["linked"], input["linked"], dev);
    }
    for (auto& el : input.items()) {
        persistent[el.key()] = el.value();
    }
    data.save();
    // Update the device from here
}

void DevicesDatabase::htmlOutput(std::string& str)
{
    std::stringstream read;
    read << data.j;
    str = read.str();
    genauto::removeNewLines(str);
}


DevicesDatabase DevicesDatabase::deviceBase("../database/devices.json");


JsonFile::JsonFile(const char* fileName) : filename(fileName)
{
    load();
}

void JsonFile::load()
{
    std::ifstream file(filename, std::ifstream::binary);
    if (file.is_open()) {
        file >> j;
        file.close();
    }
}


void JsonFile::save()
{
    std::ofstream file(filename);
    file << j;
    file.close();
}

JsonFile JsonFile::deviceIds("../database/deviceIds.json");

void DevicesDatabase::generate(CapabilitiesMessage* msg, std::string deviceId)
{
    deviceBase.data.j[deviceId]["inputs"] = {};
    deviceBase.data.j[deviceId]["outputs"] = {};
    deviceBase.data.j[deviceId]["name"] = ("Device " + deviceId);
    update(msg, deviceId);
    deviceBase.data.save();
}


static json createEncoder(std::string max, std::string min, std::string units)
{
    return {
        {"data", {{"max", max}, {"min", min}, {"units", units}}, },
        {"persistent", {"name", "Encoder"}},
        {"tag", "encoder"},
        {"type", "encoder"}
    };
}

static json createButton()
{
    return {
        {"tag", "button"},
        {"type", "button"},
    };
}

static void constructDevice(Capability device, json& output)
{
    output["tag"] = deviceTypeToString(device.type);
    dlog("Updating %s - %d\n", deviceTypeToString(device.type), device.id);
    switch (device.type) {
        case Pwm:
            output["data"] = {{"max", "inf"},{"min", "-inf"},{"units", "%"}};
            output["persistent"] = {{"linked", json::array()},{"increment", "5"},{"name", std::string("Pwm " + std::to_string(device.id))}};
            output["type"] = deviceTypeToString(Encoder);
            break;
        case Stepper:
            output["data"] = {{"max", "inf"},{"min", "-inf"},{"units", "degrees"}};
            output["persistent"] = {{"linked", json::array()},{"increment", "90"},{"name", ("Stepper " + std::to_string(device.id))},{"units", "degrees"}};
            output["type"] = deviceTypeToString(Encoder);
            break;
        case Analog:
            output["data"] = {{"max", "3.3"},{"min", "0"}};
            output["persistent"] = {{"name", "Analog " + std::to_string(device.id)},{"normalize", "3.3"},{"units", "V"}};
            output["type"] = deviceTypeToString(Analog);
            break;
        case Button:
            output["persistent"] = json::object({{"name", ("Button " + std::to_string(device.id))}});
            output["type"] = deviceTypeToString(Button);
            break;
        case Encoder:
            output["persistent"] = json::object({{"name", ("Encoder " + std::to_string(device.id))}});
            output["type"] = deviceTypeToString(Encoder);
            break;
        case Switch:
            output["persistent"] = json::object({{"linked", json::array()},{"name", ("Switch " + std::to_string(device.id))}});
            output["type"] = deviceTypeToString(Button);
            break;
        default:
            break;
    }
}

void DevicesDatabase::update(CapabilitiesMessage* msg, std::string deviceId)
{
    Capability* list = msg->capablities();
    uint16_t count = msg->count();
    auto& device = deviceBase.data.j[deviceId];
    if (device.is_null()) {
        return;
    }
    dlog("Count = %d\n", count);
    for (int i = 0 ; i < count; i++) {
        Capability& cap = list[i];
        std::string id = std::to_string(cap.id);
        std::string type = deviceTypeToString(cap.type);
        dlog("updating %s-%d\n", deviceTypeToString(cap.type), cap.id);
        if (device["inputs"].contains(id) && deviceBase.data.j[deviceId]["inputs"][id]["tag"] == type) {
            dlog("Skipping %s-%d\n", deviceTypeToString(cap.type), cap.id);
            continue;
        } else if (device["outputs"].contains(id) && deviceBase.data.j[deviceId]["outputs"][id]["tag"] == type) {
            dlog("Skipping %s-%d\n", deviceTypeToString(cap.type), cap.id);
            continue;
        } else {
            std::cout << device["outputs"].contains(id) << "\n";
            std::cout << deviceBase.data.j[deviceId]["outputs"][id]["type"] << "\n";
            dlog("Device did not contain %s - %d creating\n", deviceTypeToString(cap.type), cap.id);
            dlog("Device did not contain %s - %s creating\n", deviceTypeToString(cap.type), id.c_str());
        }
        json dev;
        switch (cap.type) {
            case Pwm:
            case Stepper:
            case Switch:
                constructDevice(cap, device["outputs"][id]);
            break;
            case Analog:
            case Button:
            case Encoder:
                constructDevice(cap, deviceBase.data.j[deviceId]["inputs"][id]);
            break;
        }
    }
    std::vector<std::string> remove;
    for (auto& el : deviceBase.data.j[deviceId]["inputs"].items()) {
        bool found = false;
        for (int i = 0; i < count; i++) {
            if (el.key() == std::to_string(list[i].id)) {
                found = true;
                break;
            }
        }
        if (!found) {
            remove.push_back(el.key());
        }
    }
    for (auto& el : remove) {
        deviceBase.data.j[deviceId]["inputs"].erase(el);
    }
    remove.clear();
    for (auto& el : deviceBase.data.j[deviceId]["outputs"].items()) {
        bool found = false;
        for (int i = 0; i < count; i++) {
            if (el.key() == std::to_string(list[i].id)) {
                found = true;
                break;
            }
        }
        if (!found) {
            remove.push_back(el.key());
        }
    }

    for (auto& el : remove) {
        deviceBase.data.j[deviceId]["outputs"].erase(el);
    }
    DevicesDatabase::deviceBase.data.save();
}

bool DevicesDatabase::exists(std::string deviceId)
{
    return !deviceBase.data.j[deviceId].is_null();
}

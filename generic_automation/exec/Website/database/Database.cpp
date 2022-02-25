#include "Database.hpp"
#include "../common/Common.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <trantor/utils/Logger.h>

using namespace genauto;
DevicesDatabase::DevicesDatabase(const char* fileName) : data(fileName)
{
    data.load();
}

void DevicesDatabase::update(
    const std::string& keystring, const std::string& type, const json& input)
{
    LOG_DEBUG << "Updating: " << keystring;
    std::stringstream str(keystring);
    std::string device;
    std::string subDevice;
    getline(str, device, ':');
    getline(str, subDevice, ':');
    auto& persistent = data.j[device][type][subDevice]["persistent"];
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
    update(msg, deviceId);
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
    output["type"] = deviceTypeToString(device.type);
    output["tag"] = deviceTypeToString(device.type);
    switch (device.type) {
        case Pwm:
            output["persistent"] = {{"increment", "5"},{"name", std::string("PWM " + std::to_string(device.id))}};
            break;
        case Stepper:
            output["data"] = {{"max", "inf"},{"min", "-inf"},{"units", "degrees"}};
            output["persistent"] = {{"increment", "90"},{"name", ("Stepper " + std::to_string(device.id))},{"units", "degrees"}};
            break;
        case Analog:
            output["data"] = {{"max", "3.3"},{"min", "0"}};
            output["persistent"] = {{"name", "Analog " + std::to_string(device.id)},{"normalize", "3.3"},{"units", "V"}};
            break;
        case Button:
            output["persistent"] = {"name", ("Button " + std::to_string(device.id))};
            break;
        case Encoder:
            output["persistent"] = {"name", ("Encoder " + std::to_string(device.id))};
            break;
        case Switch:
            output["persistent"] = {"name", ("Switch " + std::to_string(device.id))};
            break;
        default:
        return;
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
    for (int i = 0 ; i < count; i++) {
        Capability& cap = list[i];
        std::string id = std::to_string(cap.id);
        std::string type = deviceTypeToString(cap.type);
        if (!device["inputs"][id].is_null() && device["inputs"][id]["type"] == type) {
            continue;
        } else if (!device["outputs"][id].is_null() && device["outputs"][id]["type"] == type) {
            continue;
        }
        switch (cap.type) {
            case Pwm:
            case Stepper:
            case Switch:
                constructDevice(cap, device["outputs"][id]);
            break;
            case Analog:
            case Button:
            case Encoder:
                constructDevice(cap, device["inputs"][id]);
            break;
        }
    }
    for (auto& el : device.items()) {
        bool found = false;
        for (int i = 0; i < count; i++) {
            if (el.key() != std::to_string(list[i].id)) {
                
            }
        }
    }
}

bool DevicesDatabase::exists(std::string deviceId)
{
    return !deviceBase.data.j[deviceId].is_null();
}
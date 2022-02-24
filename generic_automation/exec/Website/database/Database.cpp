#include "Database.h"
#include "../common/Common.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <trantor/utils/Logger.h>

using namespace genauto;
Database::Database(const char* fileName) : fileName(fileName)
{
    load();
}

void Database::load()
{
    std::ifstream file(fileName, std::ifstream::binary);
    if (file.is_open()) {
        file >> data;
        file.close();
    }
}

void Database::update(
    const std::string& keystring, const std::string& type, const json& input)
{
    LOG_DEBUG << "Updating: " << keystring;
    std::stringstream str(keystring);
    std::string device;
    std::string subDevice;
    getline(str, device, ':');
    getline(str, subDevice, ':');
    auto& persistent = data[device][type][subDevice]["persistent"];
    for (auto& el : input.items()) {
        persistent[el.key()] = el.value();
    }
    // Update the device from here
}

void Database::save()
{
    std::ofstream file(fileName);
    file << data;
    file.close();
}

void Database::htmlOutput(std::string& str)
{
    std::stringstream read;
    read << data;
    str = read.str();
    genauto::removeNewLines(str);
}


Database Database::deviceBase("../database/devices.json");


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
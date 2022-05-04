#pragma once
#include <string>
#include "../json/json.hpp"
#include "Capabilities.hpp"

// for convenience
using json = nlohmann::json;

namespace genauto {
    class JsonFile {
    public:
        const char* filename;
        JsonFile(const char* fileName);
        json j;
        void save();
        void load();
        static JsonFile deviceIds;
        static JsonFile tasks;
        static JsonFile timedEvents;
    };
    class DevicesDatabase {
    public:

        DevicesDatabase(const char* fileName);

        void update(
            const std::string& keystring, const std::string& type, const json& input);

        
        JsonFile data;

        void htmlOutput(std::string& data);

        static DevicesDatabase deviceBase;

        // Generate the json into the devices database
        static void generate(CapabilitiesMessage* msg, std::string deviceId);

        // If any discrepencies are found, update
        static void update(CapabilitiesMessage* msg, std::string deviceId);

        // Check to see if the device is in existance
        static bool exists(std::string deviceId);
    };
}
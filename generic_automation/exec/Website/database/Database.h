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
    };
    class Database {
    public:
        Database(const char* fileName);
        void load();
        void update(
            const std::string& keystring, const std::string& type, const json& input);
        void save();
        void htmlOutput(std::string& data);
        static Database deviceBase;
    private:
        const char* fileName;
        json data;

    };

    class Devices {
    public:
        // Generate the json into the devices database
        static void generate(CapabilitiesMessage* msg);

        // If any discrepencies are found, update
        static void update(CapabilitiesMessage* msg);

        // Check to see if the device is in existance
        static bool exists(CapabilitiesMessage* msg);
    };
}
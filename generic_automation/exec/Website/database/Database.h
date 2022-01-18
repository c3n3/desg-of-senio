#pragma once
#include <string>
#include "../json/json.hpp"

// for convenience
using json = nlohmann::json;

namespace genauto {
    class Database {
    public:
        Database(const char* fileName);
        void load();
        void update(
            const std::string& keystring, const std::string& type, const json& input);
        void save();
        void htmlOutput(std::string& data);
    private:
        const char* fileName;
        json data;
    };
}
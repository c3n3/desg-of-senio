#pragma once
#include <string>
#include <nlohmann/json.hpp>

// for convenience
using json = nlohmann::json;

namespace genauto {
    class Database {
    public:
        Database(const char* fileName);
        void update(const std::string& keystring, const json& input);
        void save();
    private:
        const char* fileName;
        json data;
    };
}
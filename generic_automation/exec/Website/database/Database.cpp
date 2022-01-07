#include "Database.h"
#include <fstream>
#include <trantor/utils/Logger.h>

using namespace genauto;
Database::Database(const char* fileName) : fileName(fileName)
{
    std::ifstream file(fileName, std::ifstream::binary);
    if (file.is_open()) {
        file >> data;
        file.close();
    }
}

void Database::update(const std::string& keystring, const json& input)
{
    // Update the device from here
}

void Database::save()
{
    std::ofstream file(fileName);
    file << data;
    file.close();
}

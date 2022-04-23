#include "Task.hpp"
#include "../lib/Common/include/Log.hpp"
using namespace genauto;

Task::Task(json& j)
{
    if (!j.is_array()) {
        elog("Json is not an array\n");
        return;
    }
    for (auto& el : j.items()) {
        commands.push_back(Command(el.value()));
    }
}

bool Task::exec()
{
    for (auto& command : commands) {
        command.execute();
    }
    delete this;
    return false;
}

json Task::toJson()
{
    json j;
    for (auto& command : commands) {
        j.push_back(command.toJson());
    }
    return j;
}

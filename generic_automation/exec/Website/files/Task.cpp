#include "Task.hpp"
#include "../lib/Common/include/Log.hpp"
using namespace genauto;

Task::Task(json& j, std::string name) : name(name)
{
    if (running_.count(name)) {
        elog("Task already running created\n");
        return;
    }
    running_.insert(name);
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
    Task::running_.erase(Task::running_.find(name));
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


std::set<std::string> Task::running_;


bool Task::running(std::string name)
{
    return running_.count(name);
}

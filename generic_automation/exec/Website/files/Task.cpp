#include "Task.hpp"
#include "../lib/Common/include/Log.hpp"
using namespace genauto;

Task::Task(json& j, std::string name) : name(name), commandIt(0)
{
    if (running_.count(name)) {
        elog("Task already running created\n");
        return;
    }
    running_.insert(std::make_pair(name, this));
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
    auto& command = commands[commandIt];
    command.execute();
    commandIt++;
    if (commandIt >= commands.size()) {
        Task::running_.erase(Task::running_.find(name));
        delete this;
        return false;
    }
    return true;
}

void Task::cleanup()
{
    Task::running_.erase(Task::running_.find(name));
    delete this;
}

json Task::toJson()
{
    json j;
    for (auto& command : commands) {
        j.push_back(command.toJson());
    }
    return j;
}


std::map<std::string, Task*> Task::running_;

void Task::stopTask(std::string name)
{
    if (running_.count(name)) {
        running_[name]->stop();
    }
}


bool Task::running(std::string name)
{
    return running_.count(name);
}

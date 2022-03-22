#include "../include/SubscribeManager.hpp"

using namespace genauto;

void SubscribeManager::execute()
{
    
}

SubscribeManager::SubscribeManager(minor_t minor, Router* devRouter)
    : Device(minor), devRouter_(devRouter)
{
}

#include "../include/Router.hpp"
#include <iostream>
Router::Router()
{
}

bool Router::inMap(MessageId iD)
{
    if (idMap.contains(iD) == true)
    {
        return true;
    }
    else
        return false;
}

void Router::subscribe(Subscriber *sub, MessageId iD)
{
    if (inMap(iD) == true)
    {
        idMap[iD].insert(sub);
    }
    else
        add(sub, iD);
}

void Router::add(Subscriber *sub, MessageId iD)
{
    idMap.insert(Pair<MessageId, std::set<Subscriber *>>(iD, std::set<Subscriber *>({})));
    idMap[iD].insert(sub);
}

void Router::addPublisher(Publisher *pub)
{
    pubCount[pub]++;
    pubs.insert(pub);
}

void Router::removePublisher(Publisher *pub)
{
    auto res = pubs.find(pub);
    if (res != pubs.end()) {
        uint16_t value = pubCount[pub];
        pubCount[pub] =  value != 0 ? value - 1 : 0;
        if (pubCount[pub] == 0)
            pubs.erase(res);
    }
}

void Router::subscribeToMajor(Subscriber *sub, major_t majorId)
{
    if (majorIdMap.contains(majorId) == false)
    {
        majorIdMap.insert(Pair<major_t, std::set<Subscriber *>>(majorId, std::set<Subscriber *>({})));
    }

    majorIdMap[majorId].insert(sub);
}

void Router::removeSubscribeToMajor(Subscriber *sub, major_t majorId)
{
    if (majorIdMap.contains(majorId) == true)
    {
        auto& set = majorIdMap[majorId];
        auto find = set.find(sub);
        if (find != set.end())
        {
            set.erase(find);
        }
    }
}

void Router::removeSubscribe(Subscriber *sub, MessageId iD)
{
    if (idMap.contains(iD) == true)
    {
        auto& set = idMap[iD];
        auto find = set.find(sub);
        if (find != set.end())
        {
            set.erase(find);
        }
    }
}

void Router::execute()
{

    for (auto &pub : pubs)
    {
        Message *msg = pub->tryGet();
        if (msg != NULL)
        {
            MessageId id = msg->id();
            major_t majorId = id.getMajor();
            for (auto &sub : idMap[id])
            {
                if (sub != NULL)
                {
                    sub->receive(msg);
                }
            }

            for (auto &sub : majorIdMap[majorId])
            {
                if (sub != NULL)
                {
                    sub->receive(msg);
                }
            }
        }
    }
}

void Router::print()
{
    for (auto& kv : idMap) {
        for (auto& sub : idMap[kv.one]) {
            dlog("ID: {0x%x,%d}, Sub: %p\n", kv.one.major,kv.one.minor, sub);
        }
    }
}

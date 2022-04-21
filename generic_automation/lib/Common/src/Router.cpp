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
    dlog("adding sub to {0x%x,%d}\n", iD.major, iD.minor);
    
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
            std::cout << "Subscriber at: " << *find << " Unsubscribed from: "
                        << " Major: " << majorId << "\n";
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
            std::cout << "Subscriber at: " << *find << " Unsubscribed from: "
                        << " MessageId: " << iD.major << ":" << iD.minor << "\n";
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
            dlog("Got message: {0x%x,%d}\n", msg->id().major, msg->id().minor);
            dlog("Does contain %d\n", idMap.contains(msg->id()));
            for (auto &sub : idMap[id])
            {
                if (sub != NULL)
                {
                    dlog("Is receiving\n");
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

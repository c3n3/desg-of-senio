#include "../include/Router.hpp"


bool Router::inMap(MessageId iD)
{
    if(idMap.contains(MessageId (iD)) == true)
    {
        return true;
    }
    else
        return false;
}

void Router::Subscribe(Subscriber* sub, MessageId iD)
{
    if(inMap(iD) == true)
    {
        idMap[iD].pushBack(sub);
    }
}

void Router::Add(Subscriber* sub, MessageId iD)
{
    idMap.insert(Pair<MessageId, List<Subscriber*>>(iD, List<Subscriber*>(25)));
    idMap[iD].pushBack(sub);
}

void Router::addPublisher(Publisher* pub)
{
    pubs.pushBack(pub);
}

void Router::Execute()
{
    Publisher* pub;
    pub->tryGet();
    
}

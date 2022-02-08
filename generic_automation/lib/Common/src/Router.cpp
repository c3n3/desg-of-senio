#include "../include/Router.hpp"

bool Router::inMap(Message iD)
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
        idMap[iD].pushback(sub);
    }
}

void Router::Add(Subscriber* sub, MessageId iD)
{
    List<Subscriber*> subs = new List<Subscriber*>(sub);
    idMap[iD].insert(sub);
}

void addPublisher(Publisher* pub)
{
    List<Publisher*> pubs = new List<Subscriber*>(pub);
}

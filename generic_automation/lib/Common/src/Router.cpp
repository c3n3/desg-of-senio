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

void Router::Add(MessageId iD)
{
    subs = new List<Subscriber*>;

}
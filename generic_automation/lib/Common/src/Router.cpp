#include "../include/Router.hpp"

<<<<<<< HEAD


bool Router::inMap(MessageId iD)
=======
bool Router::inMap(Message iD)
>>>>>>> 80f920e173ffe0e531c85b38e499b810a88b313e
{
    if(idMap.contains(MessageId (iD)) == true)
    {
        return true;
    }
    else
        return false;
}

<<<<<<< HEAD

=======
>>>>>>> 80f920e173ffe0e531c85b38e499b810a88b313e
void Router::Subscribe(Subscriber* sub, MessageId iD)
{
    if(inMap(iD) == true)
    {
<<<<<<< HEAD
        idMap[iD].pushBack(sub);
    }
    
}

void Router::Add(MessageId iD)
{
    subs = new List<Subscriber*>;

}
=======
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
>>>>>>> 80f920e173ffe0e531c85b38e499b810a88b313e

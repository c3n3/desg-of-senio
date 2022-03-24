   #include "../include/Router.hpp"
   #include <iostream>
   Router::Router()
   {}

   bool Router::inMap(MessageId iD)
   {
       if(idMap.contains(iD) == true)
       {
           return true;
       }
       else
           return false;
   }

   void Router::subscribe(Subscriber* sub, MessageId iD)
   {
       if(inMap(iD) == true)
       {
           idMap[iD].push_back(sub);
       }
       else
         add(sub, iD);
   }

   void Router::add(Subscriber* sub, MessageId iD)
   {
       idMap.insert(Pair<MessageId, std::vector<Subscriber*>>(iD, std::vector<Subscriber*>({})));
       idMap[iD].push_back(sub);
       std::cout << idMap[iD].size();
   }

   void Router::addPublisher(Publisher* pub)
   {
       pubs.push_back(pub);
   }

   void Router::subscribeToMajor(Subscriber* sub, major_t majorId)
   {
       if(majorIdMap.contains(majorId) == false)
       {
           majorIdMap.insert(Pair<major_t, std::vector<Subscriber*>>(majorId, std::vector<Subscriber*>({})));
       }
           
        majorIdMap[majorId].push_back(sub);
        std::cout << majorIdMap[majorId].size();
   }

   void Router::removeSubscribeToMajor(major_t majorId)
   {
       if(majorIdMap.contains(majorId) == true)
       {
           majorIdMap[majorId].pop_back();
       }
       
   }

   void Router::removeSubscribe(MessageId iD)
   {
       if(idMap.contains(iD) == true)
       {
           idMap[iD].pop_back();
       }
   }

  void Router::execute()
  {
     
     for(auto& pub : pubs)
     {
         Message* msg = pub->tryGet();
         MessageId id = msg->id();
         major_t majorId = id.getMajor();
         if(msg != NULL)
         {
             for(auto& sub : idMap[id])
             {
                if(sub != NULL)
                {
                    sub->receive(msg);
                }
                 
             }

             for(auto& sub : majorIdMap[majorId])
             {
                if(sub != NULL)
                {
                    sub->receive(msg);
                }
                 
             }
         }
     }
     
    
  }

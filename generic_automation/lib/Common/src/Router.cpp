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
   }

   void Router::removeSubscribeToMajor(Subscriber* sub, major_t majorId)
   {
       if(majorIdMap.contains(majorId) == true)
       { 
           for(int i = 0; i < majorIdMap[majorId].size(); i++)
           {
                if(sub == majorIdMap[majorId][i])
                {
                    majorIdMap[majorId].erase(majorIdMap[majorId].begin()+i);
                    std::cout << "Subscriber at: " << majorIdMap[majorId][i] << " Unsubscribed from: " << " Major: " << majorId << "\n";
                }
           }
           
       }
       
   }

   void Router::removeSubscribe(Subscriber* sub, MessageId iD)
   {
       if(idMap.contains(iD) == true)
       {
           for(int i = 0; i < idMap[iD].size(); i++)
           {
               if(sub = idMap[iD][i])
               {
                   idMap[iD].erase(idMap[iD].begin()+i);
                   std::cout << "Subscriber at: " << idMap[iD][i] << " Unsubscribed from: " << " Major: " << iD.getMajor() << " Minor: " << iD.getMinor() << "\n";
               }
           }
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

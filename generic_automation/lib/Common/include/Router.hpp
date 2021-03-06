  #ifndef __GENAUTO_ROUTER_HPP__
  #define __GENAUTO_ROUTER_HPP__

  #include "MessageId.hpp"
  #include "Subscriber.hpp"
  #include "Map.hpp"
  #include <set>
  #include "Publisher.hpp"
  #include <algorithm>

  using namespace genauto;

  namespace genauto {
       /**
        * @brief Router can can be used to route messages to a
        * a publisher
        */
       class Router {
         public:

            Map<MessageId, std::set<Subscriber*>> idMap;
            Map<major_t, std::set<Subscriber*>> majorIdMap;
            Map<Publisher*, uint16_t> pubCount;
            std::set<Subscriber*> subs;
            std::set<Publisher*> pubs;
            
               /**
                * @brief constructor
                * 
                */
               Router();

               /**
                * @brief checks if message iD is in a map
                * 
                * @param iD
                * 
                */
               bool inMap(MessageId iD);

               /**
                * @brief If message iD is in map suscribe to message iD
                * 
                * @param sub
                * @param iD
                * 
                */
               virtual void subscribe(Subscriber* sub, MessageId iD);

               /**
               * @brief Creates list of subscribers and adds message id to subscribers
               * 
               * @param sub
               * @param iD
               * 
               */
               virtual void add(Subscriber* sub, MessageId iD);

               /**
                * @brief Adds publishers to a list
                * 
                * @param pub
                *  
                */
               virtual void addPublisher(Publisher* pub);

               /**
                * @brief Removes publishers to a list
                * 
                * @param pub
                *  
                */
               virtual void removePublisher(Publisher* pub);

               /**
                * @brief subscribe to specific major ID
                * 
                * 
                */
                virtual void subscribeToMajor(Subscriber* sub, major_t majorId);

                /**
                 * @brief remove subscriber to major ID 
                 * 
                 * 
                 */
                virtual void removeSubscribeToMajor(Subscriber* sub, major_t majorId);

                /**
                 * @brief remove subscriber
                 * 
                 * 
                 */
                virtual void removeSubscribe(Subscriber* sub, MessageId iD); 

                /**
                *@brief receive message
                * 
                */
               virtual void execute();

               void print();
       };
   }

#endif

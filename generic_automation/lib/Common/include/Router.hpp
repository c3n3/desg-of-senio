#ifndef __GENAUTO_ROUTER_HPP__
#define __GENAUTO_ROUTER_HPP__

#include "MessageId.hpp"
#include "Subscriber.hpp"
#include "Map.hpp"
#include "List.hpp"
#include "Publisher.hpp"
#include "SubscribeMessage.hpp"

using namespace genauto;

namespace genauto {
    /**
    * @brief Router can can be used to route messages to a
    * a publisher
    */
    class Router {

        public:

            Map<MessageId, List<Subscriber*>> idMap;
            //List<Subscriber*> subs;
            List<Publisher*> pubs;
            Publisher pub;


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
            virtual void Subscribe(Subscriber* sub, MessageId iD);

            /**
            * @brief Creates list of subscribers and adds message id to subscribers
            * 
            * @param sub
            * @param iD
            * 
            */
            virtual void Add(Subscriber* sub, MessageId iD);

            /**
             * @brief Adds publishers to a list
             * 
             * @param pub
             *  
             */
            virtual void addPublisher(Publisher* pub);

            /**
             *@brief  
             * 
             */
            virtual void Execute();



    };
}

#endif
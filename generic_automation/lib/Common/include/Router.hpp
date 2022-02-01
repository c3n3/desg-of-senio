#ifndef __GENAUTO_ROUTER_HPP__
#define __GENAUTO_ROUTER_HPP__

#include "Subscriber.hpp"
#include "MessageId.hpp"
#include "Map.hpp"
#include "List.hpp"

using namespace genauto;

namespace genauto{

    class Router{

        public:

            Map<MessageId, List<Subscriber*>> idMap;
            List<Subscriber*> subs;


            bool inMap(MessageId iD);

            /**
             * 
             * @brief Recieves message from subscriber and takes message ID
             * 
             * @param sub
             * @param iD
             * 
             * */
            virtual void Subscribe(Subscriber* sub, MessageId iD);

            /**
             * 
             * @brief 
             * 
             * */
            virtual void Add(MessageId iD); 



    };




}


#endif
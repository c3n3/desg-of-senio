#ifndef __GENAUTO_ROUTER_HPP__
#define __GENAUTO_ROUTER_HPP__

<<<<<<< HEAD
#include "Subscriber.hpp"
#include "MessageId.hpp"
#include "Map.hpp"
#include "List.hpp"

using namespace genauto;

namespace genauto{

    class Router{
=======
#include "MessageId.hpp"
#include "Subscriber.hpp"
#include "Map.hpp"
#include "List.hpp"
#include "Publisher.hpp"

using namespace genauto;

namespace genauto {
    /**
    * @brief Router can can be used to route messages to a
    * a publisher
    */
    class Router {
>>>>>>> 80f920e173ffe0e531c85b38e499b810a88b313e

        public:

            Map<MessageId, List<Subscriber*>> idMap;
<<<<<<< HEAD
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
=======
            //List<Subscriber*> subs;

            bool inMap(Message iD);

            /**
            * @brief Receive some subscriber and message ID
            *
            * @param sub
            * @param iD
            */
            virtual void Subscribe(Subscriber* sub, MessageId iD);

            /**
            * @brief Creates list of subscribers and adds message id to subscribers
            * 
            */
            virtual void Add(Subscriber* sub, MessageId iD);

            /**
             * @brief Creates list of publishers
             * 
             * @param pub 
             */
            virtual void addPublisher(Publisher* pub);
>>>>>>> 80f920e173ffe0e531c85b38e499b810a88b313e




<<<<<<< HEAD
}


=======
    };
}

>>>>>>> 80f920e173ffe0e531c85b38e499b810a88b313e
#endif
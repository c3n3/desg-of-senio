#ifndef __GENAUTO_COMMON_H__
#define __GENAUTO_COMMON_H__

#include "Message.hpp"
#include "../json/json.hpp"
#include <string>
#include <future>

using namespace nlohmann;

namespace genauto {
    /**
     * @brief Encode string into html format
     *
     * @param data string to encode
     */
    void encode(std::string& data);

    /**
     * @brief Sends a message to message.id().to()
     *
     * @param message 
     */
    void sendTo(Message* message);
    
    /**
     * @brief Sends a message to a device
     *
     * @param message message
     * @param dev device id
     */
    void send(Message* message, major_t dev);

    /**
     * @brief remove all 
     * 
     * @param j 
     * @param ret 
     */
    void htmlOutput(json& j, std::string& ret);

    /**
     * @brief Remove newlines
     *
     * @param data
     */
    void removeNewLines(std::string& data);

    template <class F>
    void callAsync(F&& fun) {
        auto futptr = std::make_shared<std::future<void>>();
        *futptr = std::async(std::launch::async, [futptr, fun]() {
            fun();
        });
}

}

#endif

#ifndef __GENAUTO_COMMON_H__
#define __GENAUTO_COMMON_H__

#include <string>
#include <future>

namespace genauto {
    /**
     * @brief Encode string into html format
     *
     * @param data string to encode
     */
    void encode(std::string& data);

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

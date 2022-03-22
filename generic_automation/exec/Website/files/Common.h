#ifndef __GENAUTO_COMMON_H__
#define __GENAUTO_COMMON_H__

#include <string>

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
}

#endif

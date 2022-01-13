#include "Common.h"

void genauto::encode(std::string& data)
{
    std::string buffer;
    buffer.reserve(data.size());
    for(size_t pos = 0; pos != data.size(); ++pos) {
        switch(data[pos]) {
            case '&':  buffer.append("&amp;");       break;
            case '\"': buffer.append("&quot;");      break;
            case '\'': buffer.append("&apos;");      break;
            case '<':  buffer.append("&lt;");        break;
            case '>':  buffer.append("&gt;");        break;
            default:   buffer.append(&data[pos], 1); break;
        }
    }
    data.swap(buffer);
}

void genauto::removeNewLines(std::string& data)
{
    for (int i = 0; i < data.length(); i++) {
        if (data[i] == '\n') {
            data[i] = ' ';
        }
    }
}

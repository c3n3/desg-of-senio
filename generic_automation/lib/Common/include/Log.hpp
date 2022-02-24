#ifndef __GENAUTO_LOG_HPP__
#define __GENAUTO_LOG_HPP__

#ifdef ARDUINO
#include "Arduino.h"
#define _printf(...) Serial.printf(__VA_ARGS__)
#else
#include <stdio.h>
#define _printf(...) printf(__VA_ARGS__)
#endif

#define _log(...) _printf("%s:%d: ", __FILE__, __LINE__); _printf(__VA_ARGS__)

#define dlog(...) _log(__VA_ARGS__)

#define elog(...) _log(__VA_ARGS__)

#endif

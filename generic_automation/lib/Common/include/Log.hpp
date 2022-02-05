#ifndef __GENAUTO_LOG_HPP__
#define __GENAUTO_LOG_HPP__

#ifdef ARDUINO
#include "Arduino.h"
#define dlog(...) Serial.printf("%s:%d: ", __FILE__, __LINE__); Serial.printf(__VA_ARGS__)
#else
#include <stdio.h>
#define dlog(...) printf("%s:%d: ", __FILE__, __LINE__); printf(__VA_ARGS__)
#endif

#endif

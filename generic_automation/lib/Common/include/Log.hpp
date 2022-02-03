#ifndef __GENAUTO_LOG_HPP__
#define __GENAUTO_LOG_HPP__

#ifdef ARDUINO
#include "Arduino.h"
#define dlog(...) Serial.printf(__VA_ARGS__)
#else
#include <stdio.h>
#define dlog(...) printf(__VA_ARGS__)
#endif

#endif

#ifndef __GENERIC_AUTOMATION_DEBUG_HPP__
#define __GENERIC_AUTOMATION_DEBUG_HPP__

#include <stdio.h>
#define DEBUG_ENABLE

#ifdef DEBUG_ENABLE
#define LOG(...) printf("%s:%d: ", __FILE__, __LINE__); printf(__VA_ARGS__)
#elif
#define LOG(...) {}
#endif

#endif

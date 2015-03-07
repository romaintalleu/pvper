#ifndef _ASSERT_H
#define _ASSERT_H

#include <stdint.h>

#ifdef NDEBUG
#	define assert(EX)
#else
#	define assert(EX) (void)((EX) || (__assert(#EX, __FILE__, __LINE__),0))
#endif

#ifdef __cplusplus
extern "C"
#endif
void __assert(const char *message, const char *filename, const uint32_t line);

#endif
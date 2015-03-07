#ifndef __EXTERN_H
#define __EXTERN_H

#ifdef __cplusplus
#	define EXTERNC extern "C"
#	define CTOR_PRIORITY(priority) __attribute__((constructor(priority)))
#else
#	define EXTERNC
#	define CTOR_PRIORITY
#	define constexpr const
#endif

#endif
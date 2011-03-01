#ifndef _PANIC_H_
#define _PANIC_H_

#include <stdbool.h>

#include "kernel.h"
#include "console.h"

// kernel panic handling

#define STOP_MSG "Acedia has detected an error and must shutdown."

#define UNHANDLED_EXCEPTION  0x0 // unhandled exception
#define ASSERTION_FAILED     0x1 // failed assertion
#define UNKNOWN_FAILURE      0x3 // something else

#define __KHALT __asm__("cli; hlt")

// stop the kernel entirely
void _khalt(int reason, const char* msg, const char* fcn, const char *file, const char* line);

#define STRING_(x) #x
#define STRING(x) STRING_(x)

#define kpanic(msg) _khalt(UNHANDLED_EXCEPTION, msg, __PRETTY_FUNCTION__, __FILE__, STRING(__LINE__))
#define kassert(cond) if(!(cond)) { _khalt(ASSERTION_FAILED, #cond,     \
                                         __PRETTY_FUNCTION__, __FILE__, STRING(__LINE__)); }
#define kassertmsg(cond, msg) if(!(cond)) { _khalt(ASSERTION_FAILED, msg,     \
                                         __PRETTY_FUNCTION__, __FILE__, STRING(__LINE__)); }

#endif /* _PANIC_H_ */

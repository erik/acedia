#ifndef _STDDEF_H_
#define _STDDEF_H_

#include <stdint.h>

typedef typeof((int*)0 - (int*)0) ptrdiff_t;
typedef typeof(sizeof(int))       size_t;

#define NULL ((void*)0)

#endif /* _STDDEF_H_ */

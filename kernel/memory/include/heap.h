#ifndef _HEAP_H_
#define _HEAP_H_

#include <stddef.h>

#include "kernel.h"

/* defined by linker, point to start and end of kernel, respectively 
extern unsigned int* _kernel_start;
extern unsigned int* _kernel_end;*/

void* _kmalloc(unsigned int size, int align, unsigned int* phys);

/* return a pointer to a space of size, optionally aligning */

void* kmalloc(unsigned int size, int align);


#endif /* _HEAP_H_ */

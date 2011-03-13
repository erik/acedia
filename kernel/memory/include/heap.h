#ifndef _HEAP_H_
#define _HEAP_H_

#include <stddef.h>
#include <string.h>

#include "kernel.h"

/* return a pointer to a space of size, optionally aligning, and returning the
 * physical addr
 */
void* _kmalloc(unsigned int size, int align, unsigned int* phys);

/* return a pointer to a space of size, optionally aligning */
void* kmalloc(unsigned int size, int align);

/* higher level memory allocation  */
void* alloc(unsigned int size);

/* resize an allocated pointer */
void* realloc(void* ptr, size_t size);

/* free memory allocated with alloc */
void free(void* ptr);

/* init memory manager */
void init_memory();

#define MAGIC_FREE 0xFABCAB02
#define MAGIC_USED 0xFABCAB01

typedef struct mem_header {
  unsigned int magic;
  struct mem_header *next; /* pointer to next header */
  struct mem_header *prev; /* pointer to previous header */
  unsigned int size;
} mem_header_t;

#endif /* _HEAP_H_ */

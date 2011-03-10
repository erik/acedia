#include "heap.h"

unsigned int placement = 0;

void* _kmalloc(unsigned int size, int align, unsigned int* phys) {
  // silly user, need to specify a size
  if(!size) {
    return NULL;
  }

  //if placement hasn't been set, set it to the end of the kernel
  if(placement == 0) {
    placement = (unsigned int)&_kernel_end;
  }

  // align if necessary
  if(align == 1 && ((placement) & 0x0fff)) {
    placement &= 0xfffff000;
    placement += 0x1000;
  }

  if(phys) {
    *phys = placement;
  }

  unsigned int tmp = placement;
  placement += size;
  return (void*) tmp;
}

void* kmalloc(unsigned int size, int align) {
  return _kmalloc(size, align, NULL);
}

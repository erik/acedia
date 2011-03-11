#include "heap.h"

unsigned int* heap_ptr = &_kernel_end;

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

static void set_header(unsigned* ptr, mem_header_t hdr) {
  ptr[0] = hdr.magic;
  ptr[1] = (unsigned)hdr.next;
  ptr[2] = hdr.size;
}

static void set_used(void* pointer, mem_header_t* next, unsigned size) {
  mem_header_t hdr = {MAGIC_USED, next, size};
  set_header((unsigned*)pointer, hdr);
}

static void set_free(void* pointer, mem_header_t* next, unsigned size) {
  mem_header_t hdr = {MAGIC_FREE, next, size};
  set_header((unsigned*)pointer, hdr);
}

void init_memory() {  
  _kmalloc(0x1000, 1, heap_ptr);

  set_free(heap_ptr, NULL, 0x1000 - sizeof(mem_header_t));
}

void* alloc(unsigned int size) {
  struct mem_header* hdr = (mem_header_t*)heap_ptr;
  unsigned tot_size = size + sizeof(mem_header_t);

  for(; hdr; hdr = hdr->next) {
    if(hdr->magic == MAGIC_FREE) {
      unsigned sizeh = hdr->size + sizeof(mem_header_t);
      // too small, skip it
      if(sizeh <= tot_size) {
        continue;
      } else if (sizeh == tot_size) { // perfect fit!
        set_used((void*)hdr, hdr->next, size);
        return hdr + 1;
      } else if (sizeh >= tot_size) { // too big, split
        mem_header_t* next = (mem_header_t*)(hdr + tot_size);
        set_used((void*)hdr, next, size);
        set_free(next, hdr->next, sizeh - tot_size);
        return hdr + 1;
      }
      // found it, bitches
    }
  }

  // No memory
  return NULL;
}

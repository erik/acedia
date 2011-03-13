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
  ptr[2] = (unsigned)hdr.prev;
  ptr[3] = hdr.size;
}

static void set_used(void* pointer, mem_header_t* next, mem_header_t* prev, unsigned size) {
  mem_header_t hdr = {MAGIC_USED, next, prev, size};
  set_header((unsigned*)pointer, hdr);
}

static void set_free(void* pointer, mem_header_t* next, mem_header_t* prev, unsigned size) {
  mem_header_t hdr = {MAGIC_FREE, next, prev, size};
  set_header((unsigned*)pointer, hdr);
}

void init_memory() {  
  _kmalloc(0x1000, 1, heap_ptr);

  set_free(heap_ptr, NULL, NULL, 0x1000 - sizeof(mem_header_t));
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
        set_used(hdr, hdr->prev, hdr->next, size);
        return hdr + 1;
      } else if (sizeh >= tot_size) { // too big, split
        // set next pointer as tot_size bytes ahead
        unsigned int naddr = (unsigned)hdr + tot_size; /* avoid a warning about a pointer casting */
        mem_header_t* next = (mem_header_t*)naddr;
        mem_header_t* prev = (mem_header_t*)hdr->prev;
        set_free(next, next->next, hdr, tot_size - sizeh);
        set_used(hdr, next, prev, size);
        return hdr + 1;
      }
    }
  }

  // No memory
  return NULL;
}

void* realloc(void* ptr, size_t size) {
  if(!ptr) {
    return NULL;
  }

  // realloc(ptr, 0) acts like free
  if(size == 0) {
    free(ptr);
    return NULL;
  }

  unsigned hdr_pos = (unsigned)ptr - sizeof(mem_header_t);
  mem_header_t* hdr = (mem_header_t*)hdr_pos;

  // trying to reallocate a non used or nonmapped chunk of memory
  if(hdr->magic != MAGIC_USED) {
    return NULL;
  }

  // create a new pointer and copy over everything
  void* new = alloc(size);
  memcpy(new, ptr, hdr->size);

  return new;
}

void free(void* ptr) {
  // avoid NULL ptrs
  if(!ptr) {
    return;
  }

  unsigned int hdr_pos = (unsigned)ptr - sizeof(mem_header_t);
  mem_header_t* hdr = (mem_header_t*)hdr_pos;

  // trying to free memory that isn't allocated, or not part of the heap
  if(hdr->magic != MAGIC_USED) {
    return;
  } else {
    unsigned int free_size = hdr->size;
    mem_header_t* next_ptr = hdr->next;
    mem_header_t* prev_ptr = hdr->prev;
    mem_header_t* hdr_ptr  = hdr;

    mem_header_t* adj = hdr->next;

    bool fwd = false;
    bool back = false;
    
    // check if next block is also free, merge if necessary
    if(adj && adj->magic == MAGIC_FREE) {
      next_ptr = adj->next;
      prev_ptr = hdr;
      free_size += adj->size + sizeof(mem_header_t);
      fwd = true;
    }

    // check if previous block is also free, merge if necessary
    adj = hdr->prev;
    if(adj && adj->magic == MAGIC_FREE) {
      // only modify next pointer if not already set forward
      if(!fwd) {
        next_ptr = hdr;
      }
      prev_ptr = adj->prev;
      hdr_ptr = hdr->prev;
      free_size += adj->size + sizeof(mem_header_t);
      back = true;
    }

    set_free(hdr_ptr, next_ptr, prev_ptr, free_size);
  }
}

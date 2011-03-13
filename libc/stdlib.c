#include <stdlib.h>

/*
 * variables and constants for random functions
 */
static uint32_t       rand_prev = 0x12AC8FB3;
static const uint32_t rand_mult = 1103515245;
static const uint32_t rand_add  = 12345;
static const uint32_t rand_mod  = INT32_MAX;

/* random */
int rand() {
  return (int)(rand_prev = (rand_mult * rand_prev + rand_add) % rand_mod);
}

void srand(unsigned int seed) {
  rand_prev = seed;
}

/* search / sort */

void* bsearch(const void* key, const void* base, size_t num, size_t size, comparator fcn) {
  // handle special cases
  if(num == 0) {
    return NULL;
  } else if(num == 1) {
    if(!fcn(key, base)) {
      return (void*)base;
    }
    return NULL;
  }

  size_t lower = 0, upper = num - 1;
  void* ptr = NULL;
  while(lower < upper) {
    size_t index = (lower + upper) / 2;
    ptr = (char*)base + index * size;
    int val = fcn(key, ptr);
    // key is somewhere below ptr
    if(val < 0) {
      upper = index;
    } else if(val > 0) {
      lower = index + 1;
    } else { // found it!
      return ptr;
    }
  }
  return NULL;
}

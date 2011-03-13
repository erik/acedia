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

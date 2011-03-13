#ifndef _STDLIB_H_
#define _STDLIB_H_

#include <stdint.h>

/*
 * Random functions 
 */
int rand();
void srand(unsigned int seed);
#define RAND_MAX INT32_MAX

/* misc */
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#endif /* _STDLIB_H_ */

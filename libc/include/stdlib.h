#ifndef _STDLIB_H_
#define _STDLIB_H_

#include <stdint.h>
#include <stddef.h>

/*
 * Random functions 
 */
int rand();
void srand(unsigned int seed);
#define RAND_MAX INT32_MAX

/*
 * Abs functions
 */
inline int abs(int x) { return x < 0 ? -x : x; }
inline long labs(long x) { return x < 0 ? -x : x; }

/*
 * Div functions
 */
typedef struct div {
  int quot, rem;
} div_t;

typedef struct ldiv {
  long quot, rem;
} ldiv_t;

inline div_t div(int n, int d) { div_t s = {n / d, n % d}; return s;}
inline ldiv_t ldiv(long n, long d) { ldiv_t s = {n / d, n % d}; return s;}

/*
 * Search / sort functions
 */
typedef int (*comparator)(const void*, const void*);

void *bsearch (const void* key, const void* base, size_t num, size_t size, comparator fcn);

/* misc */
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#endif /* _STDLIB_H_ */

/*
* Copyright (C) 2011 by Erik Price
* 
* Permission to use, copy, modify, and/or distribute this software for any
* purpose with or without fee is hereby granted, provided that the above
* copyright notice and this permission notice appear in all copies.
* 
* THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
* WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
* ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
* WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
* ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
* OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/



#include <string.h>

void *memcpy(void *dest, const void* src, size_t n) {
  size_t i;
  /* avoid dereference of void* pointer error */
  uint8_t* d = (uint8_t*)dest;
  uint8_t* s = (uint8_t*)src;
  for(i = 0; i < n; ++i) {
    d[i] = s[i];
  }
  return d;
}

void *memmove(void* dest, const void* src, size_t n) {
  // TODO: write memmove
  return memcpy(dest, src, n);
}

void *memchr(const void *s, int c, size_t n) {
 
  uint8_t* src = (uint8_t*)s;
  size_t i;

  for(i = 0; i < n; ++i) {
    if(*src == c)
      return src;
    src++;
  }
  
  return NULL;
}

// s1 > ? +
// s2 > ? -
// s1 = ? 0
int memcmp(const void *s1, const void *s2, size_t n) {
  size_t i;
  uint8_t* sr1 = (uint8_t*)s1;
  uint8_t* sr2 = (uint8_t*)s2;

  for(i = 0; i < n; ++i) {
    if(sr1[i] != sr2[i]) {
      return sr1[i] - sr2[i];
    }
  }

  return 0;
}

void *memset(void *d, int c, size_t n) {
  size_t i;
  uint8_t* dst = (uint8_t*)d;

  for(i = 0; i < n; ++i) {
    dst[i] = (uint8_t)c;
  }

  return dst;
}

char *strcat(char *dest, const char* src) {
  return strncat(dest, src, strlen(src));
}


char *strncat(char *dest, const char* src, size_t n) {
  size_t dl = strlen(dest);
  size_t sl = strlen(src);

  size_t i;
  for(i = dl; i < dl + sl && i < dl +  n; ++i) {
    dest[i] = src[i - dl];
  }
  return dest;
}

size_t strlen(const char* str) {
  size_t i = 0;
  while(*str++ != '\0' && ++i);
  return i;
}

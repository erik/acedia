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

char* strchr(const char* str, int c) {
  const char* ptr = str;
  while(*ptr) {
    if(*ptr == c) {
      return (char*)ptr;
    }
    ptr++;
  }  
  return NULL;
}

char* strrchr(const char* str, int c) {
  const char *ptr = str + strlen(str);
  while(ptr >= str) {
    if(*ptr == c) {
      return (char*)ptr;
    }
    ptr--;
  }
  return NULL;
}

// s1 > ? +
// s2 > ? -
// s1 = ? 0
int strcmp(const char* s1, const char* s2) {
  unsigned int n1 = strlen(s1);
  unsigned int n2 = strlen(s2);
  
  unsigned int len = n1 > n2 ? n1 : n2;

  unsigned int i;
  for(i = 0; i < len; ++i, s1++, s2++) {
    if(*s1 == *s2) {
      continue;
    } else if (*s1 > *s2) {
      return 1;
    } else {
      return -1;
    }
  }

  return (int)n1 - (int)n2;
}


int strcoll(const char* s, const char* s2) {
  return 0;
}

char* strcpy(char* dest, const char* src) {
  return memcpy(dest, src, strlen(src));
}

char* strncpy(char* dest, const char* src, size_t n) {
  unsigned int len = strlen(src);
  char * ret = memcpy(dest, src, len);
  if(n > len) {
    memcpy(dest + len, 0, n - len);
  }
  return ret;
}

char* strerror(int msg) {
  return NULL;
}

size_t strlen(const char* str) {
  size_t i = 0;
  while(*str++ != '\0' && ++i);
  return i;
}

size_t strspn(const char* src, const char* accept) {
  char c;
  unsigned start = (unsigned)src;
  while((c = *src++)) {
    int pos = -1;
    int i;
    for(i = 0; accept[i]; ++i) {
      if(c != accept[i]) 
        continue;
      pos = i;
      break;
    }

    if(pos == -1) {
      break;
    }
  }

  return (size_t)(src - 1) - start;
}

size_t strcspn(const char* src, const char* reject) {
  char c;
  unsigned start = (unsigned)src;
  while((c = *src++)) {
    int pos = -1;
    int i;
    for(i = 0; reject[i]; ++i) {
      if(c == reject[i]) {
        pos = i;
        break;
      }
    }

    if(pos != -1) {
      break;
    }
  }
  return (size_t)(src - 1) - start;
}

char* strpbrk(const char* src, const char* accept) {
  char c;
  while((c = *src++)) {
    int pos = -1;
    int i;
    for(i = 0; accept[i]; ++i) {
      if(c != accept[i]) {
        continue;
      }
      pos = i;
      break;
    }
    
    if(pos != -1) {
      return (char*)src - 1;
    }
  }
  
  return NULL;
}

char *strstr(const char* src, const char* search) {
  unsigned len = strlen(search);
  while(*src) {
    unsigned i = 0;
    while(src[i] == search[i] && i++ < len);
    if(i == len)
      return (char*)src;
    else
      src++;
  }
  return NULL;
}

char* tokptr = NULL;

char *strtok(char* src, const char* delim) {
  return strtok_r(src, delim, &tokptr);
}


/* adapted from Redhat's implementation */
char *strtok_r(char *src, const char *delim, char **save) {
  char *tok;

  if (!src) {
    src = *save;
  }
  
  /* skip past leading characters */
  src += strspn (src, delim);
  if (*src == '\0') {
    *save = src;
    return NULL;
  }
  
  /* find the end of the token */
  tok = src;
  src = strpbrk (tok, delim);
  /* if last token in string */
  if (src == NULL) {    
    *tok = '\0';
    *save = tok + 1;
  }  else {
    /* end the token and advance the save pointer past it */
    *src = '\0';
    *save = src + 1;
  }
  return tok;
}

size_t strxfrm(char *dest, const char* src, size_t n) {
  return 0;
}

#ifndef _STRING_H_
#define _STRING_H_

#include <stddef.h>
#include <stdint.h>

//      copies n bytes between two memory areas; if there is overlap, the behavior is undefined
void *memcpy(void *dest, const void *src, size_t n);

//	copies n bytes between two memory areas; unlike with memcpy the areas may overlap
void *memmove(void *dest, const void *src, size_t n); 

// 	returns a pointer to the first occurrence of c in the first n bytes of s, or NULL if not found
void *memchr(const void *s, int c, size_t n);

//	compares the first n bytes of two memory areas
int memcmp(const void *s1, const void *s2, size_t n); 

//	overwrites a memory area with n copies of c
void *memset(void *, int c, size_t n); 

// 	appends the string src to dest
char *strcat(char *dest, const char *src);

// 	appends at most n bytes of the string src to dest
char *strncat(char *dest, const char *src, size_t n);

// 	locates character c in a string, searching from the beginning
char *strchr(const char *, int c);

//	locates character c in a string, searching from the end
char *strrchr(const char *, int c); 

// 	compares two strings lexicographically
int strcmp(const char *, const char *);

//	compares up to the first n bytes of two strings lexicographically
int strncmp(const char *, const char *, size_t n); 

//	compares two strings using the current locales collating order
int strcoll(const char *, const char *); 

//     copies a string from one location to another
char *strcpy(char *dest, const char *src); 	

//	write exactly n bytes to dest, copying from src or add 0s
char *strncpy(char *dest, const char *src, size_t n); 

// 	returns the string representation of an error number e.g. errno (not thread-safe)
char *strerror(int);

// 	finds the length of a C string
size_t strlen(const char *);

// 	determines the length of the maximal initial substring consisting entirely of characters in accept
size_t strspn(const char *, const char *accept);

//	determines the length of the maximal initial substring consisting entirely of characters not in reject
size_t strcspn(const char *, const char *reject); 

// 	finds the first occurrence of any character in accept
char *strpbrk(const char *, const char *accept);

//      finds the first occurrence of the string "needle" in the longer string "haystack"
char *strstr(const char *haystack, const char *needle); 	

// 	parses a string into a sequence of tokens; non-thread safe in the spec, non-reentrant
char *strtok(char *, const char * delim);

// 	transforms src into a collating form, such that the numerical sort order of the
//      transformed string is equivalent to the collating order of src
size_t strxfrm(char *dest, const char *src, size_t n);


#endif /* _STRING_H_ */

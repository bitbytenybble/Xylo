#ifndef _STRING_H
#define _STRING_H 1

#include <sys/cdefs.h>

#include <stddef.h>


int memcmp(const void*, const void*, size_t);
void* memcpy(void* __restrict, const void* __restrict, size_t);
void* memmove(void*, const void*, size_t);

// Implement above prototypes^^^^^^^


void* memset(void* buffptr, int value, size_t size);
size_t strlen(const char* str);

#endif

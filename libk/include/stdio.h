#ifndef _STDIO_H
#define _STDIO_H 1

#include <sys/cdefs.h>

#define EOF (-1)

int printf(const char* formatString, ...);
int putchar(int c);
int puts(const char *s);

#endif

#ifndef _STDLIB_H
#define _STDLIB_H 1

#include <sys/cdefs.h>

// Informs the compiler that the function does not return.
// The compiler can then perform optimizations by removing code that is never reached.
__attribute__((__noreturn__))
void abort(void);

#endif

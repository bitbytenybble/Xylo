#include <stdio.h>
#include <stdlib.h>

// Informs the compiler that the function does not return.
// The compiler can then perform optimizations by removing code that is never reached.
__attribute__((__noreturn__))
void abort(void) {

	#if defined(__is_libk)
		// TODO: Add proper kernel panic.
		printf("kernel: panic: abort()\n");
	#else
		// TODO: Abnormally terminate the process as if by SIGABRT.
		printf("abort()\n");
	#endif

	while (1); // Hang

}

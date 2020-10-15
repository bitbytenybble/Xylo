#include <kernel/terminal.h>

#include <stdio.h>
#include "terminal_tests/test_printf.h"
#include "../arch/i386/gdt.h"



// First, let's do some basic checks to make sure we are using our x86-elf cross-compiler correctly
#if defined(__linux__)
	#error "This code must be compiled with a cross-compiler"
#elif !defined(__i386__)
	#error "This code must be compiled with an x86-elf compiler"
#endif





void kernel_main() {
	initializeTerminal();
	initGDT();

	test_scroll2();


	test_scroll2();
}

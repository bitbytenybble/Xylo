#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>


// TODO look up self-promoting types
// TODO MAKE ALL FUNCTIONS IN THIS FILE MACROS
// Prototypes
static int vprintf(const char* formatString, va_list args);
static char * intToString(unsigned val, unsigned base);

// TODO implement below
// TODO add more types to print
// TODO support bases for integer types (base 10, 2, etc)
/*
static int printUnsigned(unsigned val);
static int printLong(long val);
static int printFloat(int val);
static int printDouble(int val);
*/
int printf(const char* formatString, ...) {
	va_list funcParameters;
	va_start(funcParameters, formatString);
	int numArgs = vprintf(formatString, funcParameters);
	va_end(funcParameters);
	return numArgs;
}

// Clear memory for strings. In case no arguments are passed but string flags
// are used, the string held in the last call gets outputted.


static int vprintf(const char* formatString, va_list args) {
	unsigned int count = 0; // TODO RETURN COUNT
	char * str = NULL;
	int d;

	for (int i=0; formatString[i] != '\0'; i++){

		if (formatString[i] == '%'){
			i++;

			switch (formatString[i]) {
				case 's':
					str = va_arg(args, char*);
					puts(str);
					break;

				case 'c':
					d = va_arg(args,int);
					putchar((char)d);
					break;

				case 'd':
					d = (int) va_arg(args,int);
					if (d < 0){
						putchar('-');
						d = -d;
					}
					str = intToString(d, 10);
					puts(str);
					// TODO implement need integer to string function
					break;

				case 'f': // TODO implement
					break;

				case 'l': // TODO implement
					// TODO check if next character is 'f' to print doubles
					break;

				case 'p':
					puts("0x");
					// Keep newly defined variables in local scope
					{
						void *v = va_arg(args, void*);
						unsigned long ul = (unsigned long) v; //TODO handle 32-bit vs 64-bit addresses
						str = intToString(ul, 16);
						puts(str);
					}
					break;

				case 'x':
					// Keep newly defined variables in local scope
					{
						void *v = va_arg(args, void*);
						unsigned long ul = (unsigned long) v; //TODO handle 32-bit vs 64-bit addresses
						str = intToString(ul, 16);
						puts(str);
					}
					break;

				default:  // TODO implement print "not implemented or incorrect format"
					break;
			}

		}
		else putchar(formatString[i]);
	}

	return count;
}


// TODO use abort if incorrect base is used
static char * intToString(unsigned val, unsigned base){
	static char Representation[]= "0123456789ABCDEF";
    static char buffer[50];
    char *ptr;

    ptr = &buffer[49];
    *ptr = '\0';

    do {
        *--ptr = Representation[val%base];
        val /= base;
    } while(val != 0);

    return(ptr);
}

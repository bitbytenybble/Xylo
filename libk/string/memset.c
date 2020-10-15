#include <string.h>

// todo update
// Fills the first "size" number of bytes to the value held by "value"
// startign from the address held by buffptr
void* memset(void* buffptr, int value, size_t size) {

    unsigned char* buf = (unsigned char*) buffptr;
    for (size_t i = 0; i < size; i++)
		buf[i] = (unsigned char) value;

	return buffptr;
}

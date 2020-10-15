#include <string.h>

size_t strlen(const char* str) {
	size_t len = 0;
	// '\0' == (char)(0)
	while (str[len]) len++;
	return len;
}

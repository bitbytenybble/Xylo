#ifndef TERMINAL_H
#define TERMINAL_H

#include <stdint.h>
#include <stddef.h>

typedef struct {
	size_t    row;
	size_t    col;
	uint8_t   color;
	uint16_t *buffer

} Terminal;

void initializeTerminal();

void terminalPutchar(char chr);

//void terminal_write(const char* data, size_t size);

void terminalWrite(const char *str);

void clearTerminal();

void changeColor(); // TODO implement

#endif

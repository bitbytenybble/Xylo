#include <string.h>
#include <stdbool.h>
#include <kernel/terminal.h>
#include "vga.h"

// PROTOTYPES //

void scroll();





// CONSTANTS AND GLOBALS //

// This is the x86's VGA textmode buffer. To display text, we write data to this memory location
static uint16_t *const BUFFER_START = (uint16_t*) 0xB8000;

// By default, the VGA textmode buffer has a size of 80x25 characters
const int VGA_WIDTH  = 80;
const int VGA_HEIGHT = 25;

// Terminal data structure - used to store state of the VGA terminal and cursor
static Terminal terminal;







// TERMINAL STATIC/ENCAPSULATED FUNCTIONS //


/*
	Function: static inline uint8_t setColor(vga_color fg, vga_color bg)

	Description: Returns an unsigned 8-bit value that encodes the default foreground and background color for text
				 in the terminal.

	Parameters:
				vga_color fg: Enum integer value that corresponds to a color for the foreground

				vga_color bg: Enum integer value that corresponds to a color for the background

	Return: An unsigned 8-bit value encoded with a foreground and background color.
*/
static inline uint8_t setColor(vga_color fg, vga_color bg) {
	return fg | bg << 4;
}









/*
	Function: static inline uint16_t getChar(uint8_t unsigned_ascii_char)

	Description: Formats and returns an ASCII character to be displayed through VGA.

	Parameters:
				uint8_t unsigned_ascii_char: ASCII character to be displayed

	Return: An unsigned 16-bit value encoded with an ASCII character and a color each, to display the character and its
		    background in.
*/
static inline uint16_t getChar(uint8_t ascii_char) {

	return (uint16_t) ascii_char | (uint16_t) terminal.color << 8;
}







/*
	Function: static inline void putCharAt(unsigned char c, size_t x, size_t y)

	Description: Puts the given character 'c' at position (x,y) on the display.

	Parameters:
				uint8_t ascii_char: ASCII character to be displayed

				size_t x: x coordinate of position to place the character

				size_t y: y coordinate of position to place the character

	Return: void
*/
static inline void putCharAt(uint8_t ascii_char, size_t x, size_t y) {
	const size_t index = (y * VGA_WIDTH) + x;

	terminal.buffer[index] = getChar(ascii_char);
}







/*
	Function: static inline void newLine()

	Description: Moves cursor to the start of the next line.

	Parameters: N/A

	Return: void
*/
static inline void newLine(){

	terminal.col = 0;
	terminal.row++;

	if (terminal.row == VGA_HEIGHT){
		scroll();
	}
}




// TERMINAL API FUNCTIONS //



/*
	Function: void initializeTerminal()

	Description: Initializes global Terminal structure to use VGA display.
				 Row and column positions are initialized to the top left corner (0,0).
				 Foreground and background colors are set to light green and dark grey respectively.
				 Sets the starting address for the VGA text buffer. Then clears the display buffer,
				 in case any characters are stored in the buffer.

	Parameters: N/A

	Return: void
*/
void initializeTerminal() {
	terminal.row = terminal.col = 0;
	terminal.color = setColor(VGA_LIGHT_GREEN, VGA_DARK_GREY);
	terminal.buffer = BUFFER_START;
	clearTerminal();
}





/*
	Function: void clearRow(int row)

	Description: Clears the row given by the input parameter by setting
	             the buffer to display space characters ' '.

	Parameters:
				int row: Offset value in the buffer that represents the
						 row that needs to be cleared.

	Return: void
*/
void clearRow(int row){
	for (int col = 0; col < VGA_WIDTH; col ++) {
		const size_t index = (VGA_WIDTH * row) + col;
		terminal.buffer[index] = getChar(' ');
	}
}






/*
	Function: void clearTerminal()

	Description: Clears the terminal by clearing each row in the VGA
				 display buffer and then resets the cursor position to
				 the top left of the screen (0,0).

	Parameters: N/A

	Return: void
*/
void clearTerminal() {
	for (int row = 0; row < VGA_HEIGHT; row ++){
		clearRow(row);
	}

	terminal.row = terminal.col = 0;
}










/*
	Function: void terminalPutchar(char chr)

	Description: This function places a single character onto the screen.

	Parameters:
				char chr: Character to be appended to the display buffer.

	Return: void
*/
inline void terminalPutchar(char chr) {

	// Converted to unsigned to avoid arithmetic bit shifts.
	unsigned char uchr = chr;

	// If new line escape character, display a new line.
	if (uchr == '\n') {
		newLine();
	}
	else {
		putCharAt(uchr, terminal.col, terminal.row);
		terminal.col++;
		if (terminal.col == VGA_WIDTH) newLine();
	}
}






/*
	Function: void terminalWrite(const char *str)

	Description: This function writes a string to the display buffer.
				 Thereby displaying the string on-screen.

	Parameters:
				const char *str: An unmodifiable string that is copied onto
				                 the VGA display buffer.

	Return: void
*/
void terminalWrite(const char *str) {
	size_t length = strlen(str);

	for (size_t i = 0; i < length; i++){
		terminalPutchar(str[i]);
	}
}






/*

	Function: void scroll()

	Description: Produces a scroll effect in the terminal. This is done by shifting
				 the contents of the display buffer up by one row.

	Parameters: N/A

	Return: void
*/
void scroll() {
	for(terminal.row = 1; terminal.row < VGA_HEIGHT; terminal.row++) {

		for(terminal.col=0; terminal.col < VGA_WIDTH; terminal.col++){
			// position in linear array buffer = row_offset + col_offset
			// row_offset = base_0_row_num * VGA_WIDTH
			putCharAt(
				terminal.buffer[(terminal.row * VGA_WIDTH)+terminal.col],
				terminal.col, terminal.row-1
			);

		}
	}
	// Clear the last row for new input
	clearRow(VGA_HEIGHT-1);
	// Set the cursor to the last row
	terminal.row = VGA_HEIGHT-1;
	// Set the cursor to the starting column index, 0
	terminal.col = 0;
}

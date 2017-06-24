#include <stddef.h>
#include <stdint.h>

//Text mode color constants
enum vgaColor {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
}; //vgaColor

//this needs fixing because I cannot figure out how to do it
static inline uint16_t color(enum vgaColor fg, enum vgaColor bg) {
	return fg|bg;
}

static uint16_t* vgaAddress = (uint16_t*)0xB8000;

static const uint8_t VGA_WIDTH = 80;
static const uint8_t VGA_HEIGHT = 25;

static uint8_t xPos = 0;
static uint8_t yPos = 0;
static uint16_t terminalColor = 0x0B00;

void printOnPos(char c, uint8_t x, uint8_t y) {
	if(x <= VGA_WIDTH && y <= VGA_HEIGHT) {
		uint16_t index = VGA_WIDTH * y + x;
		//look up how characters should be made because right now i cannot choose color
		vgaAddress[index] = terminalColor | c;
	}
}

void clearScrn();
//my kinda own printf function
void printf(const char string[]) {

	//copy string to this location
	uint8_t position = 0;
	while(string[position] != '\0') {
			//check if the position is valid
			if(xPos == VGA_WIDTH) {
				xPos = 0;
				yPos++;
			}

			if(yPos == VGA_HEIGHT) {
				//TODO scrolling

				clearScrn();
			}

		switch(string[position]) {

		case '\n':
			xPos = 0;
			yPos++;
			break;

		default:
			printOnPos(string[position], xPos, yPos);
			//go to the next position
			xPos++;
		}
		position++;
	}
} //printf

void clearScrn() {
	for(uint8_t i = 0; i < 25; i++) {
		for(uint8_t j = 0; j < 80; j++) {
			//basically just print a space on the whole screen
			printf(" ");
		}
	}

	xPos = 0;
	yPos = 0;
} //clearScrn

extern "C" void kernelEntry(void* multibootStructure, uint32_t magicNumber) {

	clearScrn();
	printf("UselessOS v0.001\n");
	printf("All rights reserved\n");

	//kernel shouldn't return, that doesn't make sense
	//so it just keeps on going
	while(1);

} //kernelEntry
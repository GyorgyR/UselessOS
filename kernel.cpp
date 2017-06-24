#include <stddef.h>
#include <stdint.h>

void clearScrn();
void printf(const char[]);

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
uint16_t color(enum vgaColor fg, enum vgaColor bg) {
	return (fg | bg << 4) << 8 ;
}

static uint16_t* vgaAddress = (uint16_t*)0xB8000;

static const uint8_t VGA_WIDTH = 80;
static const uint8_t VGA_HEIGHT = 25;

static uint8_t xPos = 0;
static uint8_t yPos = 0;
static uint16_t terminalColor;

static char oldLines[VGA_HEIGHT][VGA_WIDTH];

static uint8_t oldLinesXPos = 0;
static uint8_t oldLinesYPos = 0;

void printOnPos(char c, uint8_t x, uint8_t y) {
	if(x <= VGA_WIDTH && y <= VGA_HEIGHT) {
		uint16_t index = VGA_WIDTH * y + x;
		//look up how characters should be made because right now i cannot choose color
		vgaAddress[index] = terminalColor | c;
	}
} //PrintOnPos

void setTerminalColor(enum vgaColor fg, enum vgaColor bg) {
	terminalColor = color(fg,bg);
}


void printHex(uint16_t number) {
	char foo[] = "0x0000\n";
	char hex[] = "0123456789ABCDEF";

	foo[2] = hex[(number >> 12) & 0x0F];
	foo[3] = hex[(number >> 8) & 0x0F];
	foo[4] = hex[(number >> 4) & 0x0F];
	foo[5] = hex[(number) & 0x0F];

	printf(foo);
} //printHex

//my kinda own printf function
void printf(const char string[]) {

	//copy string to this location
	uint8_t position = 0;
	while(string[position] != '\0') {
			//check if the position is valid
			if(xPos == VGA_WIDTH) {
				//set position on screen
				xPos = 0;
				yPos++;
			}

			if(yPos == VGA_HEIGHT) {
				//TODO scrolling

				clearScrn();

				//move everything one up
				for(int i = 1; i < 25; i++)
					for(int j = 0; j < 80; j++)
						oldLines[i-1][j] = oldLines[i][j];

				for(int i = 0; i < 24; i++)
					printf(oldLines[2]);

			}

		switch(string[position]) {

		case '\n':
			//set the position on the y axis to the next line on the screen
			xPos = 0;
			yPos++;

			//set the position in the buffer to the next line
			break;

		default:
			printOnPos(string[position], xPos, yPos);
			oldLines[yPos][xPos] = string[position];
			//go to the next position
			xPos++;
			break;
		}
		position++;
	}
} //printf

void clearScrn() {
	xPos = 0;
	yPos = 0;

	for(uint8_t i = 0; i < 25; i++) {
		for(uint8_t j = 0; j < 80; j++) {
			//basically just print a space on the whole screen
			printf(" ");
		}
	}

	xPos = 0;
	yPos = 0;
} //clearScrn

void initBuffer() {
	for(int i = 0 ; i < 25; i++)
		for(int j = 0; j< 80; j++)
			oldLines[i][j] = ' ';
}

extern "C" void kernelEntry(void* multibootStructure, uint32_t magicNumber) {

	setTerminalColor(VGA_COLOR_LIGHT_CYAN,VGA_COLOR_BLACK);
	initBuffer();
	clearScrn();
	printf("UselessOS v0.001\n");
	printf("All rights reserved\n");
	printf(oldLines[0]);
	

/*
	for(uint16_t i = 0; i<20;i++) {
		printHex(i);
	}

	printf("Hello World!\n");
	//printf(oldLines[0]);
*/
	//kernel shouldn't return, that doesn't make sense
	//so it just keeps on going
	while(1);
} //kernelEntry
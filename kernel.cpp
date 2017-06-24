
//Text mode color constants
/*
enum vgaColor {

} //vgaColor
*/

//my kinda own printf function
void printf(const char string[]) {
	unsigned short* vgaAddress = (unsigned short*)0xb8000;

	//copy string to this location
	int position = 0;
	while(string[position] != '\0') {
		vgaAddress[position] = (vgaAddress[position] & 0xFF00) | string[position];

		//go to the next position
		position++;
	}
} //printf

extern "C" void kernelEntry(void* multibootStructure, unsigned int magicNumber) {
	printf("This is the UselessOS\n");

	//kernel shouldn't return, that doesn't make sense
	//so it just keeps on going
	while(1);

} //kernelEntry
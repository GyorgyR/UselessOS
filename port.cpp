#include "port.h"

Port::Port(uint16_t portNo) {
	this->portNumber = portNo;
}

Port::~Port() {}

	/**************
	 * 8 BIT PORT *
	 **************/

//constructor fallsback to super
Port8Bit::Port8Bit(uint16_t portNo) : Port(portNo) {}

Port8Bit::~Port8Bit() {}

void Port8Bit::Write(uint8_t data) {
	__asm__ volatile("outb %0, %1" : : "a" (data), "Nd" (portNumber));
} //Write

uint8_t Port8Bit::Read() {

	uint8_t result;
	__asm__ volatile("inb %1, %0" : "=a" (result) : "Nd" (portNumber));
	return result;
} //Read

	/*******************
	 * 8 BIT SLOW PORT *
	 *******************/

//constructor fallsback to super
Port8BitSlow::Port8BitSlow(uint16_t portNo) : Port8Bit(portNo) {}

Port8BitSlow::~Port8BitSlow() {}

void Port8BitSlow::Write(uint8_t data) {
	__asm__ volatile("outb %0, %1 \n jmp 1f \n1:" : : "a" (data), "Nd" (portNumber));
} //Write

	/***************
	 * 16 BIT PORT *
	 ***************/

//constructor fallsback to super
Port16Bit::Port16Bit(uint16_t portNo) : Port(portNo) {}

Port16Bit::~Port16Bit() {}

void Port16Bit::Write(uint16_t data) {
	__asm__ volatile("outw %0, %1" : : "a" (data), "Nd" (portNumber));
} //Write

uint16_t Port16Bit::Read() {

	uint16_t result;
	__asm__ volatile("inw %1, %0" : "=a" (result) : "Nd" (portNumber));
	return result;
} //Read

	/***************
	 * 32 BIT PORT *
	 ***************/

//constructor fallsback to super
Port32Bit::Port32Bit(uint16_t portNo) : Port(portNo) {}

Port32Bit::~Port32Bit() {}

void Port32Bit::Write(uint32_t data) {
	__asm__ volatile("outl %0, %1" : : "a" (data), "Nd" (portNumber));
} //Write

uint32_t Port32Bit::Read() {

	uint32_t result;
	__asm__ volatile("inl %1, %0" : "=a" (result) : "Nd" (portNumber));
	return result;
} //Read
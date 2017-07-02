#pragma once

#include <stdint.h>

class Port {

protected:
	uint16_t portNumber;
	Port(uint16_t portNo);
	~Port();

}; //Port

class Port8Bit : public Port {

public:
	Port8Bit(uint16_t portNo);
	~Port8Bit();
	virtual void Write(uint8_t data);
	virtual uint8_t Read();
}; //Port8Bit


class Port8BitSlow : public Port8Bit {

public:
	Port8BitSlow(uint16_t portNo);
	~Port8BitSlow();
	virtual void Write(uint8_t data);
}; //Port8BitSlow

class Port16Bit : public Port {

public:
	Port16Bit(uint16_t portNo);
	~Port16Bit();
	virtual void Write(uint16_t data);
	virtual uint16_t Read();
}; //Port16Bit

class Port32Bit : public Port {

public:
	Port32Bit(uint16_t portNo);
	~Port32Bit();
	virtual void Write(uint32_t data);
	virtual uint32_t Read();
}; //Port16Bit
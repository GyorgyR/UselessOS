#pragma once

#include <stdint.h>

class GlobalDescriptorTable {

public:
	class SegmentDescriptor {
	private:
		uint16_t limitLow;
		uint16_t baseLow;
		uint8_t baseHigh;
		uint8_t accessRights;
		uint8_t limitHigh;
		uint8_t baseVeryHigh;

	public:
		SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t accessRights);
		uint32_t Base();
		uint32_t Limit();

	} __attribute__((packed)); //SegmentDescriptor

	SegmentDescriptor nullSegmentSelector;
	SegmentDescriptor unusedSegmentSelector;
	SegmentDescriptor codeSegmentSelector;
	SegmentDescriptor dataSegmentSelector;
	GlobalDescriptorTable();
	~GlobalDescriptorTable();

	uint16_t CodeSegmentSelector();
	uint16_t DataSegmentSelector();

}; //GlobalDescriptorTable
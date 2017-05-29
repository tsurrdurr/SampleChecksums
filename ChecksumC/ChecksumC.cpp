#include "stdafx.h"
#include "iostream"

unsigned short SettingsChecksum(void *Start, unsigned short Count)
{
	volatile unsigned long Sum = 0;
	unsigned short *pStart = (unsigned short *)Start;

	while (Count > 1)                        // sum words
	{
		Sum += *pStart++;
		Count -= 2;
	}

	if (Count)
		Sum += *(unsigned char *)pStart;    // add left-over byte, if any

	while (Sum >> 16)                        // fold 32-bit sum to 16 bits
		Sum = (Sum & 0xFFFF) + (Sum >> 16);

	return ~Sum;
}

int main()
{
	unsigned short structure[16] = { 
		0x2800, 0xE803, 0x0100, 0x0000, 
		0x0000, 0x0000, 0x0000, 0xFFFF, 
		0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 
		0xFFFF, 0xFFFF, 0xFFFF, 0x0000 };
	unsigned char structure2[38] = { 
		0x28, 0x00, 0xC8, 0x00, 0x01, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00 };
	unsigned long structure3[10] = {
		0x1400E803, 0x01000000,
		0x00000000, 0x0000FFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0x00000000
	};
	unsigned short result = SettingsChecksum(structure, 16);
	printf("Checksum is: %1i\n", result);
	result = SettingsChecksum(structure2, 16);
	printf("Checksum is: %1i\n", result);
	result = SettingsChecksum(structure3, 16);
	printf("Checksum is: %1i\n", result);
	int x;
	std::cin >> x;
}
#include "stdafx.h"
#include "iostream"
#include "vector"

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

void PrintChecksum(void *data)
{
	unsigned short result = SettingsChecksum(data, 20);
	printf("Checksum is: %04X\n", result);
}

int main()
{
	unsigned short structure[20] = { 
		0x2800, 0xE803, 0x0100, 0x0000, 
		0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 
		0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000 };
	unsigned char structure2[40] = { 
		0x28, 0x00, 0xC8, 0x00, 0x01, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00 };
	unsigned long structure3[10] = {
		0x1400E803, 0x01000000,
		0x00000000, 0x0000FFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0000
	};
	PrintChecksum(structure);
	PrintChecksum(structure2);
	PrintChecksum(structure3);
	int x;
	std::cin >> x;
}
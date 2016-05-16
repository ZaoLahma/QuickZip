/*
 * quick_zip.cpp
 *
 *  Created on: 15 maj 2016
 *      Author: janne
 */

#include "quick_zip.h"
#include "byte_counter.h"
#include "huffman_tree.h"
#include <string>
#include <iostream>
#include <stdio.h>

QuickZip::QuickZip()
{

}

ByteContainer QuickZip::Zip(const char* _bytes, uint32_t _size)
{
	printf("Original bit size: %d\n", _size * 8);

	/*
	 * Get frequencies of the different bytes
	 */
	ByteCounter bc(_bytes, _size);

	/*
	 * Construct a Huffman Tree
	 */
	HuffmanTree ht(bc);

	uint32_t bitSize = 0;

	/*
	 * Get the total size of the coded bit array
	 * by counting the bits needed for each
	 * byte.
	 */
	std::string code;
	for(unsigned int i = 0; i < _size; ++i)
	{
		code.clear();
		ht.GetBitCode(_bytes[i], code);
		printf("%c, got code %s\n", _bytes[i], code.c_str());
		bitSize += code.length();
	}

	/*
	 * Byte align the bit size
	 */
	printf("Bit size: %d\n", bitSize);
	while(bitSize % 8 != 0)
	{
		bitSize += 1;
	}
	printf("Byte aligned bit size: %d\n", bitSize);
	uint32_t byteSize = bitSize / 8;

	/*
	 * Finally encode the byte array to a bit
	 * array as defined by the constructed
	 * Huffman Tree
	 */
	char* byteBuffer = new char[byteSize];
	uint32_t byteOffset = 0;
	uint32_t bitNo = 0;
	for(unsigned int i = 0; i < _size; ++i)
	{
		code.clear();
		ht.GetBitCode(_bytes[i], code);

		for(unsigned int n = 0; n < code.length(); ++n)
		{
			if('0' == code.at(n))
			{
				SetBitInByte(&byteBuffer[byteOffset], bitNo, 0);
			}
			else
			{
				SetBitInByte(&byteBuffer[byteOffset], bitNo, 1);
			}
			bitNo++;
			if(bitNo > 7)
			{
				bitNo = 0;
				byteOffset++;
			}
		}
	}

	ByteContainer retVal;
	retVal.buffer = byteBuffer;
	retVal.size = byteSize;

	return retVal;
}

void QuickZip::SetBitInByte(char* _byteBuffer, uint32_t _bitNo, uint32_t _val)
{
	printf("Setting bit: %d in %p to: %d\n", _bitNo, _byteBuffer, _val);

	uint8_t* intPtr = (uint8_t*)(_byteBuffer);
	*intPtr |= _val << _bitNo;
}

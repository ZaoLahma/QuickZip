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
	 * Calculate the size needed for all characters
	 */
	uint32_t bitSize = 0;

	HuffmanVectorT huffmanVector = bc.GetHuffmanNodes();

	HuffmanVectorT::iterator huffIter = huffmanVector.begin();

	for(; huffIter != huffmanVector.end(); ++huffIter)
	{
		bitSize += 40;
	}
	bitSize += 8;

	/*
	 * Construct a Huffman Tree
	 */
	HuffmanTree ht(huffmanVector);

	/*
	 * Get the total size of the coded bit array
	 * by counting the bits needed for each
	 * byte.
	 */

	std::string code;
	for(unsigned int i = 0; i < _size; ++i)
	{
		code.clear();
		ht.SearchHuffmanTree(_bytes[i], code);
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
	 * Allocate memory and encode the byte to
	 * bit table
	 */
	char* byteBuffer = new char[byteSize];
	uint32_t byteOffset = 0;

	huffIter = huffmanVector.begin();

	for(; huffIter != huffmanVector.end(); ++huffIter)
	{
		byteBuffer[byteOffset] = (*huffIter)->c;
		byteOffset++;

		uint32_t* frequency = (uint32_t*)(&byteBuffer[byteOffset]);
		*frequency = (*huffIter)->frequency;
		byteOffset += sizeof(uint32_t);

		printf("Encoded %c with frequency: %d\n",  (*huffIter)->c, *frequency);
	}

	byteBuffer[byteOffset] = '\0';
	byteOffset++;

	printf("Byte offset: %d\n", byteOffset);

	/*
	 * Finally encode the byte array to a bit
	 * array as defined by the constructed
	 * Huffman Tree
	 */
	uint32_t bitNo = 0;
	for(unsigned int i = 0; i < _size; ++i)
	{
		code.clear();
		ht.SearchHuffmanTree(_bytes[i], code);

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

	printf("Byte offset at end of coding: %d\n", byteOffset);

	ByteContainer retVal;
	retVal.buffer = byteBuffer;
	retVal.size = byteSize;

	return retVal;
}

ByteContainer QuickZip::Unzip(const char* _bytes, uint32_t _size)
{
	uint32_t byteOffset = 0;
	HuffmanTree ht(_bytes, byteOffset);

	printf("Byte offset: %d\n", byteOffset);

	for(unsigned int i = byteOffset; i < _size; ++i)
	{
		for(unsigned int n = 0; n < 8; ++n)
		{
			char bit = GetBitInByte(&_bytes[i], n);
			printf("Bit: %c\n", bit);
		}
	}


	ByteContainer retVal;
	retVal.buffer = nullptr;
	retVal.size = 0;

	return retVal;
}

void QuickZip::SetBitInByte(char* _byteBuffer, uint32_t _bitNo, uint32_t _val)
{
	printf("Setting bit: %d in %p to: %d\n", _bitNo, _byteBuffer, _val);

	uint8_t* intPtr = (uint8_t*)(_byteBuffer);
	*intPtr |= _val << _bitNo;
}

char QuickZip::GetBitInByte(const char* _byteBuffer, uint32_t _bitNo)
{
	uint8_t intToCheck = *((uint8_t*)(_byteBuffer));

	intToCheck = intToCheck & (1 << _bitNo);

	if(intToCheck == 0)
	{
		return '0';
	}

	return '1';
}

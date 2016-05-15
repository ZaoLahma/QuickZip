/*
 * byte_counter.cpp
 *
 *  Created on: 15 maj 2016
 *      Author: janne
 */

#include "byte_counter.h"

ByteCounter::ByteCounter(char* _bytes, uint32_t _size) :
bytes(_bytes),
size(_size)
{
	ByteOccurancesT::iterator byteIter;

	for(uint32_t i = 0; i < size; ++i)
	{
		byteIter = byteMap.find(bytes[i]);

		if(byteMap.end() == byteIter)
		{
			byteMap[bytes[i]] = 1;
		}
		else
		{
			byteIter->second++;
		}
	}

	byteIter = byteMap.begin();

	for(; byteIter != byteMap.end(); ++byteIter)
	{
		printf("byte: 0x%x, no: %d\n", byteIter->first, byteIter->second);
	}
}

uint32_t ByteCounter::GetMostCommonByte(char& mostCommonByte)
{
	ByteOccurancesT::iterator byteIter = byteMap.begin();

	mostCommonByte = 0x0;
	uint32_t highestNo = 0;

	if(0 == byteMap.size())
	{
		return 0;
	}

	for(; byteIter != byteMap.end(); ++byteIter)
	{
		if(highestNo < byteIter->second)
		{
			highestNo = byteIter->second;
			mostCommonByte = byteIter->first;
		}
	}

	return 1;
}

void ByteCounter::RemoveByte(const char& byte)
{
	ByteOccurancesT::iterator byteIter = byteMap.find(byte);

	if(byteMap.end() != byteIter)
	{
		byteMap.erase(byteIter);
	}
}

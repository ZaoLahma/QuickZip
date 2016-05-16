/*
 * byte_counter.cpp
 *
 *  Created on: 15 maj 2016
 *      Author: janne
 */

#include "byte_counter.h"

ByteCounter::ByteCounter(const char* _bytes, uint32_t _size) :
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
}

ByteOccurancesT& ByteCounter::GetByteMap()
{
	return byteMap;
}

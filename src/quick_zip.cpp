/*
 * quick_zip.cpp
 *
 *  Created on: 15 maj 2016
 *      Author: janne
 */

#include "quick_zip.h"
#include "byte_counter.h"
#include "huffman_tree.h"

QuickZip::QuickZip()
{

}

const char* QuickZip::Zip(char* _bytes, uint32_t _size)
{
	ByteCounter bc(_bytes, _size);
	HuffmanTree ht;

	char mostCommonByte;

	while(0 != bc.GetMostCommonByte(mostCommonByte))
	{
		ht.AddEntry(mostCommonByte);
		bc.RemoveByte(mostCommonByte);
	}

	for(uint32_t i = 0; i < _size; ++i)
	{
		printf("Substitute: 0x%x with %d ones\n", _bytes[i], ht.GetLevel(_bytes[i]));
	}

	return nullptr;
}

const char* QuickZip::Unzip(char* _bytes, uint32_t _size)
{
	return nullptr;
}

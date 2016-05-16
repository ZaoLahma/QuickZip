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

QuickZip::QuickZip()
{

}

const char* QuickZip::Zip(const char* _bytes, uint32_t _size)
{
	//Get frequencies of the different bytes
	ByteCounter bc(_bytes, _size);

	//Construct a Huffman Tree
	HuffmanTree ht(bc);

	//Get a string representation of the bit pattern for each byte
	std::string code;
	for(unsigned int i = 0; i < _size; ++i)
	{
		code.clear();
		ht.GetBitCode(_bytes[i], code);
		printf("%c, got code %s\n", _bytes[i], code.c_str());
	}

	return nullptr;
}

const char* QuickZip::Unzip(char* _bytes, uint32_t _size)
{
	return nullptr;
}

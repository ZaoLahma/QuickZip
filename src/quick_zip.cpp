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
	ByteCounter bc(_bytes, _size);
	HuffmanTree ht(bc);

	return nullptr;
}

const char* QuickZip::Unzip(char* _bytes, uint32_t _size)
{
	return nullptr;
}

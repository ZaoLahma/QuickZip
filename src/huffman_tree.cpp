/*
 * huffman_tree.cpp
 *
 *  Created on: 15 maj 2016
 *      Author: janne
 */

#include "huffman_tree.h"

HuffmanTree::HuffmanTree() : currentLevel(0)
{

}

void HuffmanTree::AddEntry(const char& byte)
{
	map[byte] = currentLevel;
	currentLevel++;
}

uint32_t HuffmanTree::GetLevel(const char& byte)
{
	return map.find(byte)->second;
}

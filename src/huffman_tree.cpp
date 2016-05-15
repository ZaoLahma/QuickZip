/*
 * huffman_tree.cpp
 *
 *  Created on: 15 maj 2016
 *      Author: janne
 */

#include "huffman_tree.h"

HuffmanTree::HuffmanTree(ByteCounter& _bc) : bc(_bc)
{
	entry = nullptr;

	ByteOccurancesT byteMap = bc.GetByteMap();

	ByteOccurancesT::iterator byteIter = byteMap.begin();

	for( ; byteIter != byteMap.end(); ++byteIter)
	{
		HuffmanNode* newEntry = new HuffmanNode();
		newEntry->c = byteIter->first;
		newEntry->frequency = byteIter->second;
		huffmanVector.push_back(newEntry);
	}

	HuffmanNode* left = GetLowestWeight();
	HuffmanNode* right = GetLowestWeight();
}

HuffmanNode* HuffmanTree::GetLowestWeight()
{
	HuffmanNode* retVal = nullptr;
	uint32_t lowestValue = 0xffffffff;
	for(unsigned int i = 0; i < huffmanVector.size(); ++i)
	{
		if(lowestValue > huffmanVector[i]->frequency)
		{
			lowestValue = huffmanVector[i]->frequency;
			retVal = huffmanVector[i];
		}
	}

	return retVal;
}

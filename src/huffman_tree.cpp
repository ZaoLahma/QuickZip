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

	ByteOccurancesT& byteMap = bc.GetByteMap();

	ByteOccurancesT::iterator byteIter = byteMap.begin();

	for( ; byteIter != byteMap.end(); ++byteIter)
	{
		HuffmanNode* newEntry = new HuffmanNode();
		newEntry->c = byteIter->first;
		newEntry->frequency = byteIter->second;
		newEntry->right = nullptr;
		newEntry->left = nullptr;
		huffmanVector.push_back(newEntry);
	}


	while(huffmanVector.size() > 1)
	{
		HuffmanNode* right = GetLowestWeight();
		HuffmanNode* left = GetLowestWeight();

		HuffmanNode* rootItem = new HuffmanNode();
		rootItem->frequency = left->frequency + right->frequency;
		rootItem->left = left;
		rootItem->right = right;

		printf("left: %d, right: %d\n", left->frequency, right->frequency);

		huffmanVector.push_back(rootItem);
	}

	entry = huffmanVector[0];
}

HuffmanNode* HuffmanTree::GetLowestWeight()
{
	HuffmanNode* retVal = nullptr;
	uint32_t lowestValue = 0xffffffff;

	HuffmanVectorT::iterator huffIter = huffmanVector.begin();
	HuffmanVectorT::iterator smallestEntry = huffmanVector.begin();

	for( ; huffIter != huffmanVector.end(); ++huffIter)
	{
		if(lowestValue > (*huffIter)->frequency)
		{
			lowestValue = (*huffIter)->frequency;
			smallestEntry = huffIter;
		}
	}

	retVal = (*smallestEntry);

	huffmanVector.erase(smallestEntry);

	printf("Returning value: %d\n", retVal->frequency);

	return retVal;
}

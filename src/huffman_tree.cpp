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

	/*
	 * Construct a Huffman Node (leaf) for
	 * all characters.
	 */
	HuffmanVectorT huffmanVector;
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

	huffmanNodeStorage = huffmanVector;


	/*
	 * Build the Huffman Tree using the following algorithm:
	 *
	 * Remove the two leaves with the lowest occurance from the
	 * list of leaves.
	 *
	 * "Combine" them under a root node.
	 *
	 * Add the two combined leaves' frequencies to the root node.
	 *
	 * Add the root node to list of leaves.
	 *
	 * Repeat until only one element remains in the list of leaves.
	 * This will be the entry point to the Huffman Tree.
	 */
	while(huffmanVector.size() > 1)
	{
		HuffmanNode* right = GetLowestWeight(huffmanVector);
		HuffmanNode* left = GetLowestWeight(huffmanVector);

		HuffmanNode* rootItem = new HuffmanNode();
		rootItem->frequency = left->frequency + right->frequency;
		rootItem->left = left;
		rootItem->right = right;

		printf("left: %d, right: %d\n", left->frequency, right->frequency);

		huffmanVector.push_back(rootItem);
		huffmanNodeStorage.push_back(rootItem);
	}

	entry = huffmanVector[0];
}

HuffmanTree::~HuffmanTree()
{
	for(unsigned int i = 0; i < huffmanNodeStorage.size(); ++i)
	{
		delete huffmanNodeStorage[i];
	}

	huffmanNodeStorage.clear();
}

bool HuffmanTree::GetBitCode(const char& searchPattern, std::string& code)
{
	return GetBitCode(searchPattern, entry, code);
}

bool HuffmanTree::GetBitCode(const char& searchPattern, HuffmanNode* entryPoint, std::string& code)
{
	/*
	 * This function performs a recursive search down through the
	 * Huffman Tree until it finds the searchPattern.
	 *
	 * If nothing is found, it will return an empty string.
	 */

	if(entryPoint == nullptr)
	{
		return false;
	}

	if(entryPoint->left == nullptr && entryPoint->right == nullptr)
	{
		/*
		 * We hit a leaf. Need to check if it contains our searchPattern.
		 */
		if(entryPoint->c == searchPattern)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		/*
		 * Continue searching down the tree.
		 */
		std::string tmpString;
		bool retVal = GetBitCode(searchPattern, entryPoint->left, tmpString);
		if(retVal)
		{
			code += "0";
			code += tmpString;
		}
		else
		{
			tmpString.clear();
			retVal = GetBitCode(searchPattern, entryPoint->right, tmpString);
			if(retVal)
			{
				code += "1";
				code += tmpString;
			}
		}
		return retVal;
	}
}

HuffmanNode* HuffmanTree::GetLowestWeight(HuffmanVectorT& huffmanVector)
{
	/*
	 * Help function for constructing the Huffman Tree.
	 *
	 * It returns the leaf with the lowest frequency
	 * and removes it from the list of leaves.
	 */

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

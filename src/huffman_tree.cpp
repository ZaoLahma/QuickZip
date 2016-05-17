/*
 * huffman_tree.cpp
 *
 *  Created on: 15 maj 2016
 *      Author: janne
 */

#include "huffman_tree.h"

HuffmanTree::HuffmanTree(HuffmanVectorT _huffmanVector)
{
	entry = nullptr;

	huffmanNodeStorage = _huffmanVector;

	BuildHuffmanTree(_huffmanVector);

	entry = _huffmanVector[0];
}

HuffmanTree::HuffmanTree(const char* _encoudedBuffer)
{
	HuffmanVectorT huffmanVector;

	const char* currentByte = _encoudedBuffer;
	uint32_t byteOffset = 0;
	while('\0' != *currentByte)
	{
		HuffmanNode* currentNode = new HuffmanNode();
		currentByte = &_encoudedBuffer[byteOffset];
		currentNode->c = *currentByte;
		byteOffset++;
		uint32_t* intPtr = (uint32_t*)(&_encoudedBuffer[byteOffset]);
		currentNode->frequency = *intPtr;

		huffmanVector.push_back(currentNode);

		byteOffset += sizeof(uint32_t);
		currentByte = &_encoudedBuffer[byteOffset];
	}

	huffmanNodeStorage = huffmanVector;

	BuildHuffmanTree(huffmanVector);
}

void HuffmanTree::BuildHuffmanTree(HuffmanVectorT& _huffmanVector)
{
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
	while(_huffmanVector.size() > 1)
	{
		HuffmanNode* right = GetLowestWeight(_huffmanVector);
		HuffmanNode* left = GetLowestWeight(_huffmanVector);

		HuffmanNode* rootItem = new HuffmanNode();
		rootItem->frequency = left->frequency + right->frequency;
		rootItem->left = left;
		rootItem->right = right;

		printf("left: %d, right: %d\n", left->frequency, right->frequency);

		_huffmanVector.push_back(rootItem);
		huffmanNodeStorage.push_back(rootItem);
	}
}

HuffmanTree::~HuffmanTree()
{
	for(unsigned int i = 0; i < huffmanNodeStorage.size(); ++i)
	{
		delete huffmanNodeStorage[i];
	}

	huffmanNodeStorage.clear();
}

HuffmanNode* HuffmanTree::SearchHuffmanTree(const char& searchPattern, std::string& code)
{
	return SearchHuffmanTree(searchPattern, entry, code);
}

HuffmanNode* HuffmanTree::SearchHuffmanTree(const char& searchPattern, HuffmanNode* entryPoint, std::string& code)
{
	/*
	 * This function performs a recursive search down through the
	 * Huffman Tree until it finds the searchPattern.
	 *
	 * If nothing is found, it will return an empty string.
	 */

	if(entryPoint == nullptr)
	{
		return nullptr;
	}

	if(entryPoint->left == nullptr && entryPoint->right == nullptr)
	{
		/*
		 * We hit a leaf. Need to check if it contains our searchPattern.
		 */
		if(entryPoint->c == searchPattern)
		{
			return entryPoint;
		}
		else
		{
			return nullptr;
		}
	}
	else
	{
		/*
		 * Continue searching down the tree.
		 */
		std::string tmpString;
		HuffmanNode* retVal = SearchHuffmanTree(searchPattern, entryPoint->left, tmpString);
		if(nullptr != retVal)
		{
			code += "0";
			code += tmpString;
		}
		else
		{
			tmpString.clear();
			retVal = SearchHuffmanTree(searchPattern, entryPoint->right, tmpString);
			if(nullptr != retVal)
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

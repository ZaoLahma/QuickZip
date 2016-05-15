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
}

void HuffmanTree::AddEntry(const char& left, const char& right)
{
	HuffmanNode* leftNode = new HuffmanNode();
	leftNode->c = left;

	HuffmanNode* rightNode = new HuffmanNode();
	rightNode->c = right;

	HuffmanNode* root = new HuffmanNode();

	root->left = leftNode;
	root->right = rightNode;

	entry = root;
}

uint32_t HuffmanTree::GetLevel(const char& byte)
{
	return 0;
}

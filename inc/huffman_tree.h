/*
 * huffman_tree.h
 *
 *  Created on: 15 maj 2016
 *      Author: janne
 */

#ifndef INC_HUFFMAN_TREE_H_
#define INC_HUFFMAN_TREE_H_

#include <map>
#include "byte_counter.h"

typedef std::map<char, uint32_t> HuffmanMapT;

struct HuffmanNode
{
	char c;
	uint32_t weight;
	HuffmanNode* left = nullptr;
	HuffmanNode* right = nullptr;
};

class HuffmanTree
{
public:
	HuffmanTree(ByteCounter& _bc);

	void AddEntry(const char& left, const char& right);

	uint32_t GetLevel(const char& byte);

protected:

private:
	HuffmanTree();
	HuffmanNode* entry;
	ByteCounter bc;
};



#endif /* INC_HUFFMAN_TREE_H_ */

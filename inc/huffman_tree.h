/*
 * huffman_tree.h
 *
 *  Created on: 15 maj 2016
 *      Author: janne
 */

#ifndef INC_HUFFMAN_TREE_H_
#define INC_HUFFMAN_TREE_H_

#include <map>
#include <vector>
#include <string>
#include "byte_counter.h"

struct HuffmanNode
{
	char c;
	std::string code;
	uint32_t frequency;
	HuffmanNode* left = nullptr;
	HuffmanNode* right = nullptr;
};

typedef std::vector<HuffmanNode*> HuffmanVectorT;

class HuffmanTree
{
public:
	HuffmanTree(ByteCounter& _bc);

	bool GetBitCode(const char& searchPatter, std::string& code);

protected:

private:
	HuffmanTree();
	HuffmanNode* entry;
	ByteCounter& bc;

	HuffmanVectorT huffmanVector;

	bool GetBitCode(const char& searchPattern, HuffmanNode* entryPoint, std::string& code);
	HuffmanNode* GetLowestWeight();
};



#endif /* INC_HUFFMAN_TREE_H_ */

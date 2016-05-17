/*
 * huffman_tree.h
 *
 *  Created on: 15 maj 2016
 *      Author: janne
 */

#ifndef INC_HUFFMAN_TREE_H_
#define INC_HUFFMAN_TREE_H_

#include <string>
#include "byte_counter.h"
#include "quick_zip_types.h"

class HuffmanTree
{
public:
	HuffmanTree(HuffmanVectorT _huffmanVector);
	HuffmanTree(const char* _encodedBuffer, uint32_t& _byteOffset);
	~HuffmanTree();

	HuffmanNode* FindByteInTreeTree(const char& searchPattern, std::string& code);

	HuffmanNode* FindByteFromBitCode(const std::string& code);

protected:

private:
	HuffmanTree();
	HuffmanNode* entry;

	HuffmanVectorT huffmanNodeStorage;

	void BuildHuffmanTree(HuffmanVectorT& _huffmanVector);

	HuffmanNode* SearchHuffmanTree(const char& searchPattern, HuffmanNode* entryPoint, std::string& code);
	HuffmanNode* GetLowestWeight(HuffmanVectorT& huffmanVector);
};



#endif /* INC_HUFFMAN_TREE_H_ */

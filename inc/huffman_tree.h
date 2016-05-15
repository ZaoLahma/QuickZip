/*
 * huffman_tree.h
 *
 *  Created on: 15 maj 2016
 *      Author: janne
 */

#ifndef INC_HUFFMAN_TREE_H_
#define INC_HUFFMAN_TREE_H_

#include <map>

typedef std::map<char, uint32_t> HuffmanMapT;

class HuffmanTree
{
public:
	HuffmanTree();

	void AddEntry(const char& byte);

	uint32_t GetLevel(const char& byte);

protected:

private:
	HuffmanMapT map;
	uint32_t currentLevel;
};



#endif /* INC_HUFFMAN_TREE_H_ */

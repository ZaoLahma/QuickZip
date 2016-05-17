/*
 * quick_zip.h
 *
 *  Created on: 15 maj 2016
 *      Author: janne
 */

#ifndef INC_QUICK_ZIP_H_
#define INC_QUICK_ZIP_H_

#include <cstdint>

struct ByteContainer
{
	uint32_t size;
	char* buffer;
};

/*
 * QuickZip - A byte compression class
 * using Huffman Coding as compression
 * algorithm.
 *
 * Still not implemented:
 * 	- Encoding of the byte to bit table
 * 	- Decoding an encoded bit array, obviously
 */

class QuickZip
{
public:
	QuickZip();

	ByteContainer Zip(const char* _bytes, uint32_t _size);

	ByteContainer Unzip(const char* _bytes, uint32_t _size);

protected:

private:
	void SetBitInByte(char* _byteBuffer, uint32_t _bitNo, uint32_t _val);

	char GetBitInByte(const char* _byteBuffer, uint32_t _bitNo);
};



#endif /* INC_QUICK_ZIP_H_ */

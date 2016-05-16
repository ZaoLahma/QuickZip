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

class QuickZip
{
public:
	QuickZip();

	ByteContainer Zip(const char* _bytes, uint32_t _size);

protected:

private:
	void SetBitInByte(char* _byteBuffer, uint32_t _bitNo, uint32_t _val);
};



#endif /* INC_QUICK_ZIP_H_ */

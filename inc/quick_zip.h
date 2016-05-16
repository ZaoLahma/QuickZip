/*
 * quick_zip.h
 *
 *  Created on: 15 maj 2016
 *      Author: janne
 */

#ifndef INC_QUICK_ZIP_H_
#define INC_QUICK_ZIP_H_

#include <cstdint>

class QuickZip
{
public:
	QuickZip();

	const char* Zip(const char* _bytes, uint32_t _size);

	const char* Unzip(char* _bytes, uint32_t _size);

protected:

private:
	void SetBitInByte(char* _byteBuffer, uint32_t _bitNo, uint32_t _val);
	char GetBit(char* _byteBuffer, uint32_t _bitNo);
};



#endif /* INC_QUICK_ZIP_H_ */

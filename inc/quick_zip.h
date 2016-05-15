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
};



#endif /* INC_QUICK_ZIP_H_ */

/*
 * byte_counter.h
 *
 *  Created on: 15 maj 2016
 *      Author: janne
 */

#ifndef INC_BYTE_COUNTER_H_
#define INC_BYTE_COUNTER_H_

#include <cstdint>

class ByteCounter
{
public:
	ByteCounter(char* _bytes, uint32_t _size);

protected:

private:
	char* bytes;
	uint32_t size;

};



#endif /* INC_BYTE_COUNTER_H_ */

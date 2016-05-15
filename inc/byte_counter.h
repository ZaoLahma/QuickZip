/*
 * byte_counter.h
 *
 *  Created on: 15 maj 2016
 *      Author: janne
 */

#ifndef INC_BYTE_COUNTER_H_
#define INC_BYTE_COUNTER_H_

#include <cstdint>
#include <map>

typedef std::map<char, uint32_t> ByteOccurancesT;

class ByteCounter
{
public:
	ByteCounter(char* _bytes, uint32_t _size);

	uint32_t GetMostCommonByte(char& c);

	void RemoveByte(const char&);

protected:

private:
	char* bytes;
	uint32_t size;

	ByteOccurancesT byteMap;
};



#endif /* INC_BYTE_COUNTER_H_ */

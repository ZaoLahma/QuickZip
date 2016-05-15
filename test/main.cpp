/*
 * main.cpp
 *
 *  Created on: 15 maj 2016
 *      Author: janne
 */

#include "byte_counter.h"
#include "quick_zip.h"
#include <iostream>

#define ASSERT_EQ(_this, _that) \
if(_this != _that) \
{ \
	std::cout<<_this<<" is not "<<_that<<std::endl; \
	return 1; \
}

int main(void)
{
	char* byteArray = new char[6];
	byteArray[0] = 57;
	byteArray[1] = 58;
	byteArray[2] = 59;
	byteArray[3] = 59;
	byteArray[4] = 57;
	byteArray[5] = 57;

	ByteCounter bc(byteArray, 6);

	char mostCommonByte;

	bc.GetMostCommonByte(mostCommonByte);
	ASSERT_EQ(57, mostCommonByte);
	bc.RemoveByte(57);

	bc.GetMostCommonByte(mostCommonByte);
	ASSERT_EQ(59, mostCommonByte);
	bc.RemoveByte(59);

	bc.GetMostCommonByte(mostCommonByte);
	ASSERT_EQ(58, mostCommonByte);

	QuickZip qz;

	qz.Zip(byteArray, 6);

	return 0;
}

/*
 * main.cpp
 *
 *  Created on: 15 maj 2016
 *      Author: janne
 */

#include "byte_counter.h"
#include "quick_zip.h"
#include <iostream>
#include <string>

#define ASSERT_EQ(_this, _that) \
if(_this != _that) \
{ \
	std::cout<<_this<<" is not "<<_that<<std::endl; \
	return 1; \
}

int main(void)
{
	std::string byteArray = "eebbeecdebeeebecceeeddebbbeceedebeeddeeeecceeeedeeedeeebeedeceedebeeedeceeedebee";

	ByteCounter bc(byteArray.c_str(), byteArray.length());

	return 0;
}

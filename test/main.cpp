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
#include <fstream>

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

	QuickZip qz;
	ByteContainer zipped = qz.Zip(byteArray.c_str(), byteArray.length());

	ASSERT_EQ(39, zipped.size);

	ByteContainer unzipped = qz.Unzip(zipped.buffer, zipped.size);

	ASSERT_EQ(unzipped.size, byteArray.length());

	for(uint32_t i = 0; i < byteArray.length(); ++i)
	{
		ASSERT_EQ(byteArray.at(i), unzipped.buffer[i])
	}

	delete[] zipped.buffer;
	delete[] unzipped.buffer;

	std::streampos size;
	std::ifstream stream("./src/quick_zip.cpp", std::ios::in | std::ios::binary | std::ios::ate);
	size = stream.tellg();

	char* fileBuffer = new char[size];

    stream.seekg (0, std::ios::beg);
    stream.read (fileBuffer, size);
    stream.close();

    uint32_t fileSize = size;

    printf("Got size: %d\n", fileSize);

    ByteContainer zippedFile = qz.Zip(fileBuffer, size);

    printf("zippedFile.size: %d\n", zippedFile.size);

    delete[] zippedFile.buffer;

	return 0;
}

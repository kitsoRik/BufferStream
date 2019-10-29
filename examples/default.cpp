#include <vector>
#include <list>
#include <map>
#include <iostream>
#include "BufferStream.h"

int main()
{
	Buffer buffer;
	BufferStream readStream (&buffer, BufferStream::ReadOnly);

	unsigned char uc = 255;
	signed char cc = 66;
	char c = 'k';
	int i = 5423198;
	long l = 15522344;
	
	readStream << uc;
	readStream << cc;
	readStream << c;
	readStream << i;
	readStream << l;

	BufferStream writeStream (&buffer, BufferStream::WriteOnly);

	unsigned char uc2;
	signed char cc2;
	char c2;
	int i2;
	long l2;

	writeStream >> uc2;
	writeStream >> cc2;
	writeStream >> c2;
	writeStream >> i2;
	writeStream >> l2;
	
	std::cout << (int)uc2 << '!' << (int)cc2 << '!'
				<< c2 << '!' << i2 << '!'
				<< l2;
	
	return 0;
}
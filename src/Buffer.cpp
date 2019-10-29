#include "Buffer.h"

Buffer::Buffer() : array(nullptr), size(0)
{

}

Buffer::Buffer(char* s) : array(nullptr), size(0)
{
	*this = fromUtf8(static_cast<const char*>(s));
}

Buffer::Buffer(const char* s) : array(nullptr), size(0)
{
	*this = fromUtf8(s);
}

#ifdef USE_STL
Buffer::Buffer(const std::string& str)
{
	*this = fromUtf8(str);
}
#endif

Buffer::Buffer(const char* s, const unsigned int& size)
{
	*this = fromUtf8(s, size);
}

void Buffer::append(const char& c)
{
	resize(size + 1);
	array[size - 1] = c;
}

void Buffer::append(const char* c, const unsigned int& size)
{
	unsigned int oldSize = this->size;
	resize(this->size + size);
	for (unsigned int i = oldSize; i < this->size; i++)
	{
		array[i] = c[i];
	}
}

void Buffer::resize(const unsigned int& size)
{
	if (this->size == size)
		return;
	char* s = new char[size + 1];

	unsigned int i;
	for (i = 0; i < size && i < this->size; i++)
	{
		s[i] = array[i];
	}
	for (; i < size; i++)
		s[i] = 0;
	s[size] = 0;

	this->size = size;

	delete array;
	array = s;
}

char* Buffer::toBytes()
{
	unsigned int fullSize = size + 4;
	char* data = new char[fullSize];
	for (unsigned int i = 0; i < 4; i++)
	{
		data[i] = static_cast<char>(size >> i * 8);
	}
	for (unsigned int i = 4; i < fullSize; i++)
	{
		data[i] = array[i - 4];
	}

	return data;
}

Buffer Buffer::fromBytes(char* s)
{
	Buffer buffer;

	char* temp_size = new char[4];
	for (unsigned int i = 0; i < 4; i++)
	{
		temp_size[i] = s[i];
	}


	buffer.size = *reinterpret_cast<unsigned int*>(temp_size);

	buffer.array = new char[buffer.size];
	for (unsigned int i = 0; i < buffer.size; i++)
	{
		buffer.array[i] = s[i + 4];
	}

	return buffer;
}

#ifdef USE_STL
Buffer Buffer::fromUtf8(const std::string & str)
{
	return fromUtf8(str.c_str(), static_cast<unsigned int>(str.size()));
}
#endif

Buffer Buffer::fromUtf8(const char* s)
{
	unsigned int size = 0;
	while (s[size++]);
	return fromUtf8(s, size);
}

Buffer Buffer::fromUtf8(const char* s, const int size)
{
	return Buffer::fromUtf8(s, static_cast<unsigned int>(size));
}

Buffer Buffer::fromUtf8(const char* s, const unsigned int size)
{
	Buffer buffer;
	buffer.resize(size);
	for (unsigned int i = 0; i < size; i++)
	{
		buffer.array[i] = s[i];
	}
	return buffer;
}

char& Buffer::operator[](const unsigned int& index)
{
	return array[index];
}

Buffer::operator const char* ()
{
	return array;
}
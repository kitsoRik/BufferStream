#pragma once

#define USE_STL
#ifdef USE_STL
#include <string>
#include <list>
#include <vector>
#include <map>
#endif

class Buffer
{
	friend class BufferStream;
private:
	unsigned int size;
	char* array;

public:

	Buffer();
	Buffer(char* s);
	Buffer(const char* s);
#ifdef USE_STL
	Buffer(const std::string& str);
#endif
	Buffer(const char* s, const unsigned int& size);

	void append(const char& c);
	void append(const char* c, const unsigned int& size);
	void resize(const unsigned int& size);

	unsigned int bytesSize() { return size + sizeof(int); }

	char* toBytes();
	static Buffer fromBytes(char* s);

#ifdef USE_STL
	static Buffer fromUtf8(const std::string& str);
#endif
	static Buffer fromUtf8(const char* s);
	static Buffer fromUtf8(const char* s, const int size);
	static Buffer fromUtf8(const char* s, const unsigned int size);

	char& operator[](const unsigned int& index);
	operator const char* ();
};
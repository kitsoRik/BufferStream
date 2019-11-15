#pragma once

#include "Buffer.h"

class BufferStream
{
public:
	enum TypeStream
	{
		ReadOnly,
		WriteOnly,
		ReadWrite
	};

	BufferStream(Buffer* buffer, const TypeStream& typeStream);

	BufferStream& writeString(const char* s);
	BufferStream& readString(char*& s);

	BufferStream& writeData(const unsigned char* s, const unsigned int &size);
	BufferStream& readData(unsigned char*& d, unsigned int &size);

	BufferStream& operator <<(const char& c);
	BufferStream& operator <<(const unsigned char& c) { return *this << char(c); }
	BufferStream& operator <<(const signed char& c) { return *this << char(c); }
	BufferStream& operator <<(const bool& b);
	BufferStream& operator <<(const short& n);
	BufferStream& operator <<(const int& n);
	BufferStream& operator <<(const long& n);
	BufferStream& operator <<(const long long& n);
	BufferStream& operator <<(const unsigned short& n) { return *this << short(n); }
	BufferStream& operator <<(const unsigned int& n) { return *this << int(n); }
	BufferStream& operator <<(const unsigned long& n) { return *this << long(n); }
	BufferStream& operator <<(const unsigned long long& n) { return *this << static_cast<long long>(n); }
	BufferStream& operator <<(float& n);
	BufferStream& operator <<(double& n);

#ifdef USE_STL
	BufferStream& operator <<(const std::string& s);
	template <typename T>
	BufferStream& operator <<(const std::list<T>& l)
	{
		if (m_typeStream == WriteOnly)
			throw "Write only stream";
		*this << static_cast<unsigned int>(l.size());
		for (auto it = l.begin(); it != l.end(); it++)
		{
			*this << *it;
		}

		return *this;
	}
	template <typename T>
	BufferStream& operator<<(const std::vector<T>& v)
	{
		if (m_typeStream == WriteOnly)
			throw "Write only stream";
		*this << static_cast<unsigned int>(v.size());
		for (auto it = v.begin(); it != v.end(); it++)
		{
			*this << *it;
		}

		return *this;
	}
	template <typename T1, typename T2>
	BufferStream& operator<<(const std::map<T1, T2>& m)
	{
		if (m_typeStream == WriteOnly)
			throw "Write only stream";
		*this << static_cast<unsigned int>(m.size());
		for (auto it = m.begin(); it != m.end(); it++)
		{
			*this << it->first;
			*this << it->second;
		}

		return *this;
	}
#endif

	BufferStream& operator >> (char& c);
	BufferStream& operator >> (unsigned char& c) { return *this >> reinterpret_cast<char&>(c); }
	BufferStream& operator >> (signed char& c) { return *this >> reinterpret_cast<char&>(c); }
	BufferStream& operator >> (bool& b);
	BufferStream& operator >> (short& n);
	BufferStream& operator >> (int& n);
	BufferStream& operator >> (long& n);
	BufferStream& operator >> (long long& n);
	BufferStream& operator >> (unsigned short& n) { return *this >> reinterpret_cast<short&>(n); }
	BufferStream& operator >> (unsigned int& n) { return *this >> reinterpret_cast<int&>(n); }
	BufferStream& operator >> (unsigned long& n) { return *this >> reinterpret_cast<long&>(n); }
	BufferStream& operator >> (unsigned long long& n) { return *this >> reinterpret_cast<long long&>(n); }
	BufferStream& operator >> (float& n);
	BufferStream& operator >> (double& n);

#ifdef USE_STL
	BufferStream& operator >>(std::string& s);
	template <typename T>
	BufferStream& operator >>(std::list<T>& l)
	{
		if (m_typeStream == ReadOnly)
			throw "Read only stream";
		unsigned int size;
		*this >> size;
		l.resize(size);
		for (auto it = l.begin(); it != l.end(); it++)
		{
			int t;
			*this >> t;
			*it = t;
		}
		return *this;
	}
	template <typename T>
	BufferStream& operator>>(std::vector<T>& v)
	{
		if (m_typeStream == ReadOnly)
			throw "Read only stream";
		unsigned int size;
		*this >> size;
		v.resize(size);
		for (unsigned int i = 0; i < size; i++)
		{
			T t;
			*this >> t;
			v[i] = t;
		}
		return *this;
	}
	template <typename T1, typename T2>
	BufferStream& operator >>(std::map<T1, T2>& m)
	{
		if (m_typeStream == ReadOnly)
			throw "Read only stream";
		unsigned int size;
		*this >> size;
		for (unsigned int i = 0; i < size; i++)
		{
			T1 t1;
			T2 t2;
			*this >> t1;
			*this >> t2;
			m[t1] = t2;
		}
		return *this;
	}
#endif
	BufferStream& operator <<(const Buffer& buffer);
	BufferStream& operator >>(Buffer& buffer);

private:
	unsigned int m_readIndex;
	unsigned int m_writeIndex;

	Buffer* m_buffer;

	TypeStream m_typeStream;
};
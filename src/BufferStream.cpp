#include "BufferStream.h"

BufferStream::BufferStream(Buffer* buffer, const BufferStream::TypeStream& typeStream)
	: m_readIndex(0), m_writeIndex(0)
{
	m_buffer = buffer;
	m_typeStream = typeStream;
}

BufferStream& BufferStream::writeString(const char* s)
{
	unsigned int size = 0;
	while (s[size++]);
	*this << size;
	for (unsigned int i = 0; i < size; i++)
		* this << s[i];
	return *this;
}

BufferStream& BufferStream::readString(char*& s)
{
	unsigned int size;
	*this >> size;
	s = new char[size + 1];
	for (unsigned int i = 0; i < size; i++)
	{
		char c;
		*this >> c;
		s[i] = c;
	}
	s[size] = 0;
	return *this;
}

BufferStream& BufferStream::writeData(const unsigned char* s, const unsigned int &size)
{
	*this << size;
	for (unsigned int i = 0; i < size; i++)
		* this << s[i];
	return *this;
}

BufferStream& BufferStream::readData(unsigned char*& d, unsigned int &size)
{
	*this >> size;
	d = new unsigned char[size];
	for (unsigned int i = 0; i < size; i++)
	{
		char c;
		*this >> c;
		d[i] = c;
	}
	return *this;
}

BufferStream& BufferStream::operator <<(const char& c)
{
	if (m_typeStream == WriteOnly)
		throw "Write only stream";
	m_buffer->resize(m_buffer->size + sizeof(c));
	(*m_buffer)[m_writeIndex++] = static_cast<char>(c);
	return *this;
}

BufferStream& BufferStream::operator <<(const bool& b)
{
	if (m_typeStream == WriteOnly)
		throw "Write only stream";
	m_buffer->resize(m_buffer->size + sizeof(b));
	(*m_buffer)[m_writeIndex++] = static_cast<char>(b);
	return *this;
}

BufferStream& BufferStream::operator <<(const short& n)
{
	if (m_typeStream == WriteOnly)
		throw "Write only stream";
	m_buffer->resize(m_buffer->size + sizeof(n));
	for (unsigned int i = 0; i < sizeof(n); i++)
	{
		char c = static_cast<char>(n >> (i * 8));
		(*m_buffer)[m_writeIndex++] = c;
	}
	return *this;
}

BufferStream& BufferStream::operator <<(const int& n)
{
	if (m_typeStream == WriteOnly)
		throw "Write only stream";
	m_buffer->resize(m_buffer->size + sizeof(n));
	for (unsigned int i = 0; i < sizeof(n); i++)
	{
		char c = static_cast<char>(n >> (i * 8));
		(*m_buffer)[m_writeIndex++] = c;
	}
	return *this;
}

BufferStream& BufferStream::operator <<(const long& n)
{
	if (m_typeStream == WriteOnly)
		throw "Write only stream";
	m_buffer->resize(m_buffer->size + sizeof(n));
	for (unsigned int i = 0; i < sizeof(n); i++)
	{
		char c = static_cast<char>(n >> (i * 8));
		(*m_buffer)[m_writeIndex++] = c;
	}
	return *this;
}

BufferStream& BufferStream::operator <<(const long long& n)
{
	if (m_typeStream == WriteOnly)
		throw "Write only stream";
	m_buffer->resize(m_buffer->size + sizeof(n));
	for (unsigned int i = 0; i < sizeof(n); i++)
	{
		char c = static_cast<char>(n >> (i * 8));
		(*m_buffer)[m_writeIndex++] = c;
	}
	return *this;
}

BufferStream& BufferStream::operator <<(float& n)
{
	if (m_typeStream == WriteOnly)
		throw "Write only stream";
	m_buffer->resize(m_buffer->size + sizeof(n));
	for (unsigned int i = 0; i < sizeof(n); i++)
	{
		unsigned char *s = reinterpret_cast<unsigned char *>(&n);
		writeData(s, sizeof(n));
	}
	return *this;
}

BufferStream& BufferStream::operator <<(double& n)
{
	if (m_typeStream == WriteOnly)
		throw "Write only stream";
	m_buffer->resize(m_buffer->size + sizeof(n));
	for (unsigned int i = 0; i < sizeof(n); i++)
	{
		unsigned char *s = reinterpret_cast<unsigned char *>(&n);
		writeData(s, sizeof(n));
	}
	return *this;
}

#ifdef USE_STL
BufferStream& BufferStream::operator<<(const std::string & s)
{
	if (m_typeStream == WriteOnly)
		throw "Write only stream";
	*this << static_cast<unsigned int>(s.size());
	for (unsigned int i = 0; i < s.size(); i++)
	{
		*this << s[i];
	}

	return *this;
}
#endif

BufferStream& BufferStream::operator >> (char& c)
{
	if (m_typeStream == ReadOnly)
		throw "Read only stream";
	c = (*m_buffer)[m_readIndex++];
	return *this;
}

BufferStream& BufferStream::operator >> (bool& b)
{
	if (m_typeStream == ReadOnly)
		throw "Read only stream";
	b = static_cast<bool>((*m_buffer)[m_readIndex++]);
	return *this;
}

BufferStream& BufferStream::operator >> (short& n)
{
	if (m_typeStream == ReadOnly)
		throw "Read only stream";
	char* c = new char[sizeof(n)];
	for (unsigned int i = 0; i < sizeof(n); i++)
	{
		c[i] = (*m_buffer)[m_readIndex++];
	}
	n = *reinterpret_cast<short*>(c);
	delete[] c;
	return *this;
}

BufferStream& BufferStream::operator >> (int& n)
{
	if (m_typeStream == ReadOnly)
		throw "Read only stream";
	char* c = new char[sizeof(n)];
	for (unsigned int i = 0; i < sizeof(n); i++)
	{
		c[i] = (*m_buffer)[m_readIndex++];
	}
	n = *reinterpret_cast<int*>(c);
	delete[] c;
	return *this;
}

BufferStream& BufferStream::operator >> (long& n)
{
	if (m_typeStream == ReadOnly)
		throw "Read only stream";
	char* c = new char[sizeof(n)];
	for (unsigned int i = 0; i < sizeof(n); i++)
	{
		c[i] = (*m_buffer)[m_readIndex++];
	}
	n = *reinterpret_cast<long*>(c);
	delete[] c;
	return *this;
}

BufferStream& BufferStream::operator >> (long long& n)
{
	if (m_typeStream == ReadOnly)
		throw "Read only stream";
	char* c = new char[sizeof(n)];
	for (unsigned int i = 0; i < sizeof(n); i++)
	{
		c[i] = (*m_buffer)[m_readIndex++];
	}
	n = *reinterpret_cast<long long*>(c);
	delete[] c;
	return *this;
}

BufferStream& BufferStream::operator >> (float& n)
{
	if (m_typeStream == ReadOnly)
		throw "Read only stream";
	unsigned char* c = new unsigned char[sizeof(n)];
	unsigned int size;
	readData(c, size);
	n = *reinterpret_cast<int*>(c);
	delete[] c;
	return *this;
}

BufferStream& BufferStream::operator >> (double& n)
{
	if (m_typeStream == ReadOnly)
		throw "Read only stream";
	unsigned char* c = new unsigned char[sizeof(n)];
	unsigned int size;
	readData(c, size);
	n = *reinterpret_cast<int*>(c);
	delete[] c;
	return *this;
}

#ifdef USE_STL
BufferStream& BufferStream::operator>>(std::string & s)
{
	if (m_typeStream == ReadOnly)
		throw "Read only stream";
	unsigned int size;
	*this >> size;
	s.resize(size);
	for (unsigned int i = 0; i < size; i++)
	{
		char c;
		*this >> c;
		s[i] = c;
	}
	return *this;
}
#endif

BufferStream& BufferStream::operator <<(const Buffer& buffer)
{
	if (m_typeStream == WriteOnly)
		throw "Write only stream";
	*this << buffer.size;
	for (unsigned int i = 0; i < buffer.size; i++)
	{
		*this << buffer.array[i];
	}

	return *this;
}

BufferStream& BufferStream::operator >>(Buffer& buffer)
{
	if (m_typeStream == ReadOnly)
		throw "Read only stream";
	unsigned int size;
	*this >> size;

	buffer.resize(size);

	for (unsigned int i = 0; i < buffer.size; i++)
	{
		*this >> buffer.array[i];
	}

	return *this;
}
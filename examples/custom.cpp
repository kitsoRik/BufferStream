#include <vector>
#include <list>
#include <map>
#include <iostream>
#include "BufferStream.h"

class MyClass
{
	std::string name;
	int age;
public:
	MyClass() : name(""), age(0)
	{

	}
	MyClass(const std::string &name, const int &age)
	{
		this->name = name;
		this->age = age;
	}

	void show()
	{
		std::cout << name << " " << age << std::endl;
	}

	friend BufferStream& operator << (BufferStream &stream, const MyClass &myclass)
	{
		stream << myclass.name;
		stream << myclass.age;
		return stream;
	}

	friend BufferStream& operator >> (BufferStream &stream, MyClass &myclass)
	{
		stream >> myclass.name;
		stream >> myclass.age;
		return stream;
	}
};

int main()
{
	Buffer buffer;
	BufferStream readStream (&buffer, BufferStream::ReadOnly);

	MyClass myclass1 ("Rostyslav", 19);

	readStream << myclass1;

	BufferStream writeStream (&buffer, BufferStream::WriteOnly);

	MyClass myclass2;
	writeStream >> myclass2;

	myclass2.show();
	
	return 0;
}
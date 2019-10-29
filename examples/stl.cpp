#include <vector>
#include <list>
#include <map>
#include <iostream>
#include "BufferStream.h"

int main()
{
	std::string mystring = "Pidburachynskyi Rostyslav";
	std::list<int> mylist = {-1, 0, 1, 2, 3, 27, 228, 322, 644, 1337, 1488};
	std::vector<long long> myvector = {-11314, 100001, 141421, 218281828, 31428571};
	std::map<std::string, int> mymap = {{"February", 31}, {"January", 28}};

	Buffer buffer;
	BufferStream stream (&buffer, BufferStream::ReadWrite);

	stream << mystring;
	stream << mylist;
	stream << myvector;
	stream << mymap;

	mystring.clear();
	mylist.clear();
	myvector.clear();
	mymap.clear();

	stream >> mystring;
	stream >> mylist;
	stream >> myvector;
	stream >> mymap;

	std::cout << mystring << std::endl;
	for(auto it = mylist.begin(); it != mylist.end(); it++)
	{
		std::cout << *it << ' ';
	}
	std::cout << std::endl;
	for(auto it = myvector.begin(); it != myvector.end(); it++)
	{
		std::cout << *it << ' ';
	}
	std::cout << std::endl;
	for(auto it = mymap.begin(); it != mymap.end(); it++)
	{
		std::cout << it->first << " - " << it->second << std::endl;
	}

	return 0;
}
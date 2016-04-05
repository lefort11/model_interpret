#pragma once

#include <iostream>

using namespace std;

class String
{
	char* str;
	int length;

public:

	String(const char* source = nullptr)
	{
		length = strlen(source);
		str = new char[length+1];
		strcpy(str, source);
		str[length] = '\0';
	}

	String(char c)
	{
		str = new char(c);
	}

	String(String const& other)
	{
		length = other.length;
		str = new char[length + 1 ];
		strcpy(str, other.str);
		str[length] = '\0';
	}

	String& operator=(String const& other)
	{
		if(this != &other)
		{
			this->~String();
			new(this) String(other);
		}
		return (*this);
	}

	String& operator+=(String const& other)
	{
		length = length + other.length;
		char* temp = new char[length + 1];
		strcpy(temp, str);
		temp[length] = '\0';
		delete[] str;
		str = temp;
		strcat(str, other.str);
		return (*this);
	}


	friend ostream& operator<<(ostream& s, String const& string);

	~String()
	{
		delete[] str;
	}

};

inline ostream& operator<<(ostream& s, String const& string)
{
	s << string.str;
	return s;
}
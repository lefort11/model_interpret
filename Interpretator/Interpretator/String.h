#pragma once

#include <iostream>

using namespace std;

class String
{
	char* str;
	int length;
	int bufSize;

public:

	String(const char* source = nullptr)
	{
		length = strlen(source);
		str = new char[length+1];
		strcpy(str, source);
		str[length] = '\0';
		bufSize = length + 1;
	}

	/*String(char* source = nullptr)
	{
		length = strlen(source);
		str = new char[length + 1];
		strcpy(str, source);
		str[length] = '\0';
		bufSize = length + 1;
	} */

	String(char c)
	{
		str = new char[2];
		*str = c;
		str[1] = '\0';
		length = 1;
		bufSize = 2;
	}

	String(String const& other)
	{
		length = other.length;
		str = new char[other.bufSize];
		strcpy(str, other.str);
		for (int i = length; i < other.bufSize; ++i)
			str[i] = '\0';
		bufSize = other.bufSize;
	}

	String(int size, int fictive)
	{
		bufSize = size;
		length = 0;
		str = new char[bufSize];
		for (int i = 0; i < bufSize; ++i)
			str[i] = '\0';
	}

	String& operator=(String const& other)
	{
		/*if(this != &other)
		{
			this->~String();
			new(this) String(other);
		}
		return (*this); */
		if(this != &other)
		{
			delete[] str;
			length = other.length;
			str = new char[other.bufSize];
			strcpy(str, other.str);
			for (int i = length; i < other.bufSize; ++i)
				str[i] = '\0';
			bufSize = other.bufSize;
		}
		return (*this);
	}

	String& operator+=(String const& other)
	{
		if (bufSize - 1 <= length + other.length) //if bufer is smaller than needed
		{
			length = length + other.length;
			bufSize = length + 1;
			char* temp = new char[length + 1];
			strcpy(temp, str);
			temp[length] = '\0';
			delete[] str;
			str = temp;
			strcat(str, other.str);
		}
		else
		{
			strcat(str, other.str);
		}
		return (*this);
	}

	void Clear() const
	{
		for (int i = 0; i < bufSize; ++i)
			str[i] = '\0';
	}

	bool operator==(String const& other) const
	{
		return strcmp(str, other.str);
	}


	friend ostream& operator<<(ostream& s, String const& string);

	~String()
	{
		delete[] str;
	}

	operator char*() const
	{
		return str;
	}

	operator const char*() const
	{
		return str;
	}

};

inline ostream& operator<<(ostream& s, String const& string)
{
	s << string.str;
	return s;
}

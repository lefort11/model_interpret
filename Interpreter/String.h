#pragma once

#include <iostream>
#include "tests/testing.h"

using namespace std;

class String
{
	char* str;
	size_t length;
	size_t bufSize;

public:

	String(const char* source = nullptr)
	{
		if(source != nullptr)
		{
			length = strlen(source);
			str = new char[length + 1];
			strcpy(str, source);
			str[length] = '\0';
			bufSize = length + 1;
		}
		else
		{
			length = 0;
			str = nullptr;
			bufSize = 0;
		}
	}


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
		if(other.str != nullptr)
		{
			length = other.length;
			str = new char[other.bufSize];
			strcpy(str, other.str);
			for (auto i = length; i < other.bufSize; ++i)
				str[i] = '\0';
			bufSize = other.bufSize;
		}
		else
		{
			length = 0;
			bufSize = other.bufSize;
			str = new char[other.bufSize];
		}
	}

	String(size_t size, char ch)
	{
		bufSize = size;
		length = 0;
		str = new char[bufSize];
		for (int i = 0; i < bufSize; ++i)
			str[i] = ch;
	}

	String& operator=(String const& other)
	{

		if(this != &other)
		{
			if(other.str != nullptr)
			{
				delete[] str;
				length = other.length;
				str = new char[other.bufSize];
				strcpy(str, other.str);
				for (auto i = length; i < other.bufSize; ++i)
					str[i] = '\0';
				bufSize = other.bufSize;
			}
			else
			{
				delete[] str;
				length = 0;
				bufSize = other.bufSize;
				str = nullptr;
			}
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
			length += other.length;
		}
		return (*this);
	}

	String operator+ (String const& other) const
	{
		String temp = *this;
		temp += other;
		return temp;
	}

	bool operator> (String const& other) const
	{
		return (strcmp(str, other.str) > 0);
	}

	bool operator< (String const& other) const
	{
		return (strcmp(str, other.str) < 0);
	}

	bool operator>= (String const& other) const
	{
		return (strcmp(str, other.str) >= 0);
	}

	bool operator<= (String const& other) const
	{
		return (strcmp(str, other.str) <= 0);
	}


	void Clear() const
	{
		for (int i = 0; i < bufSize; ++i)
			str[i] = '\0';
	}

	bool operator==(String const& other) const
	{
		return strcmp(str, other.str) == 0;
	}

	bool operator!=(String const& other) const
	{
		return strcmp(str, other.str) != 0;
	}


	friend ostream& operator<<(ostream& s, String const& string);
	friend istream& operator>> (istream& s, String& string);

	~String()
	{
		if(str != nullptr)
			delete[] str;
	}

	const char* GetPtr() const
	{
		return str;
	}

	bool IsEmpty() const
	{
		return strcmp(str, "") == 0;
	}

	size_t GetLength() const
	{
		return length;
	}
	size_t GetBufSize() const
	{
		return bufSize;
	}

};

inline ostream& operator<<(ostream& s, String const& string)
{
	s << string.str;
	return s;
}

inline istream& operator >> (istream& s, String& string)
{
	char str[20];
	s >> str;
	string.Clear();
	string = String(str);
	return s;
}

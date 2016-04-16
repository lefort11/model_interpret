#pragma once

#include "String.h"

enum LexemeType
{
	LEXEME_VOID, //0
	LEXEME_PROGRAM,
	LEXEME_INT,
	LEXEME_STRING,
	LEXEME_REAL,
	LEXEME_STRUCT,
	LEXEME_INT_CONST,
	LEXEME_STRING_CONST,
	LEXEME_REAL_CONST,

	LEXEME_IF, //6
	LEXEME_ELSE,
	LEXEME_FOR,
	LEXEME_WHILE,
	LEXEME_BREAK,
	LEXEME_GOTO,
	LEXEME_READ,
	LEXEME_WRITE, //13

	LEXEME_NOT,
	LEXEME_AND,
	LEXEME_OR, //16

	LEXEME_PLUS,
	LEXEME_MINUS,
	LEXEME_MULTIPLE,
	LEXEME_DIVISION, //20
	LEXEME_SEMICOLON,
	LEXEME_LBRACKET,
	LEXEME_RBRACKET,
	LEXEME_LPARENTH,
	LEXEME_RPARENTH, //25
	LEXEME_COMMA, //26
	LEXEME_MORE,
	LEXEME_LESS,
	LEXEME_LESS_OR_EQUAL,
	LEXEME_MORE_OR_EQUAL, //30
	LEXEME_EQUAL,
	LEXEME_NOT_EQUAL,
	LEXEME_ASSIGNMENT,
	LEXEME_COLON,
	LEXEME_APOSTROPHE,
	LEXEME_QUOTE, //36
	LEXEME_POINT,

	LEXEME_NAME,
	LEXEME_END
};

class Lexeme
{
	LexemeType type;
	int value;

public:

	Lexeme(LexemeType type = LEXEME_VOID, int value = 0) : type(type), value(value) {}

	/*void Change(LexemeType type = LEXEME_VOID, int value = 0)
	{
		this->type = type;
		this->value = value;
	}

	LexemeType GetType() const
	{
		return type;
	}

	int GetValue() const
	{
		return value;
	} */

	bool operator==(Lexeme const& other)
	{
		return (type == other.type) && (value == other.value);
	}
};

enum IdentType
{
	VOID,
	INT,
	STRING,
	REAL,
	STRUCT_NAME,
	USER,
	INT_CONST,
	REAL_CONST,
	STRING_CONST
};

class Identifier
{
	IdentType type;
	String name;
	int intValue;
	float realValue;
	String stringValue;

public:
	Identifier(): type(VOID), name(nullptr), intValue(0), realValue(0), stringValue(nullptr) {}
	Identifier(IdentType type, String name, int intv, float floatv, String stringv): type(type), name(name), intValue(intv), realValue(floatv), stringValue(stringv) {}

	String& GetName()
	{
		return name;
	}

	void ChangeIntValue(int v)
	{
		intValue = v;
	}

	void ChangeName(String newName)
	{
		name = newName;
	}

	IdentType GetType() const
	{
		return type;
	}
};

class LexemeTable
{
	Lexeme* ptr;
	int size;

public:

	LexemeTable() : ptr(nullptr), size(0) {}
	LexemeTable(Lexeme const& lex)
	{
		ptr = new Lexeme(lex);
		size = 1;
	}
	LexemeTable(int size) : size(size)
	{
		ptr = new Lexeme[size];
	}
	~LexemeTable()
	{
		if(size == 1)
			delete ptr;
		else
			delete[] ptr;
	}

	void Push(Lexeme const& lex)
	{
		if (ptr == nullptr)
		{
			ptr = new Lexeme(lex);
		}
		else
		{
			Lexeme* temp = new Lexeme[size+1];
			for (int i = 0; i < size; ++i)
			{
				temp[i] = ptr[i];
			}
			temp[size] = lex;
			delete[] ptr;
			ptr = temp;
		}
		++size;
	}

	Lexeme& operator[](int i)
	{
		return ptr[i];
	}

	Lexeme const& operator[](int i) const
	{
		return ptr[i];
	}

	LexemeTable& operator+= (Lexeme lex)
	{
		Push(lex);
		return (*this);
	}
};

class IdentTable
{
	Identifier* ptr;
	int size;

public:

	IdentTable() : ptr(nullptr), size(0) {}
	IdentTable(Identifier const& ident)
	{
		ptr = new Identifier(ident);
		size = 1;
	}
	IdentTable(int size) : size(size)
	{
		ptr = new Identifier[size];
	}
	~IdentTable()
	{
		if(size == 1)
			delete ptr;
		else
			delete[] ptr;
	}

	void Push(Identifier const& ident)
	{
		if (ptr == nullptr)
		{
			ptr = new Identifier(ident);
		}
		else
		{
			Identifier* temp = new Identifier[size + 1];
			for (int i = 0; i < size; ++i)
			{
				temp[i] = ptr[i];
			}
			temp[size] = ident;
			delete[] ptr;
			ptr = temp;
		}
		++size;
	}

	Identifier& operator[](int i)
	{
		return ptr[i];
	}
	
	Identifier const& operator[](int i) const
	{
		return ptr[i];
	}

	int Search(const char* string) const
	{
		for (int i = 0; i < size; ++i)
			if ( ptr[i].GetName() == String(string) )
				return i;
		return -1;
	}


};

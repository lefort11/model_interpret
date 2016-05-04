#pragma once

#include "String.h"

#define BUF_SIZE 20

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

	LEXEME_IF,
	LEXEME_ELSE,
	LEXEME_FOR,
	LEXEME_WHILE,
	LEXEME_BREAK,
	LEXEME_GOTO,
	LEXEME_READ,
	LEXEME_WRITE,

	LEXEME_NOT,
	LEXEME_AND,
	LEXEME_OR,

	LEXEME_PLUS,
	LEXEME_MINUS,
	LEXEME_MULTIPLY,
	LEXEME_DIVISION,

	LEXEME_SEMICOLON,
	LEXEME_LBRACKET,
	LEXEME_RBRACKET,
	LEXEME_LPARENTH,
	LEXEME_RPARENTH,
	LEXEME_COMMA,
	LEXEME_MORE,
	LEXEME_LESS,
	LEXEME_LESS_OR_EQUAL,
	LEXEME_MORE_OR_EQUAL,
	LEXEME_EQUAL,
	LEXEME_NOT_EQUAL,
	LEXEME_ASSIGNMENT,
	LEXEME_COLON,
	LEXEME_APOSTROPHE,
	LEXEME_QUOTE,
	LEXEME_POINT,

	LEXEME_NAME,
	LEXEME_UNARY_MINUS,

	RPM_GOTO,
	RPM_FALSE_GOTO,
	RPM_LABEL,
	RPM_ADDRESS,
	RPM_OUT_OF_STACK,
	RPM_LOOP,

	LEXEME_END
};

/**************************************************/

class Lexeme
{
	LexemeType type;
	int value;
	int tableNumber;

public:

	Lexeme(LexemeType type = LEXEME_VOID, int value = 0, int tableNum = 0) : type(type), value(value), tableNumber(tableNum)
	{ }



	LexemeType GetType() const
	{
		return type;
	}

	int GetValue() const
	{
		return value;
	}

	bool operator==(Lexeme const &other) const
	{
		return ((type == other.type) && (value == other.value));
	}

	bool operator!= (Lexeme const &other) const
	{
		return ((type != other.type) || (value != other.value));
	}

	int GetTableNumber() const
	{
		return tableNumber;
	}
};

/**************************************************/

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
	STRING_CONST,
	LABEL
};


/**************************************************/
class Identifier
{
	IdentType type;
	String name;
	bool declared;
	int intValue;
	double realValue;
	String stringValue;

public:
	Identifier(): type(VOID), name(nullptr), declared(false),intValue(0), realValue(0), stringValue(nullptr) {}

	Identifier(IdentType type, String const& name, int intv, double doublev, String const& stringv): type(type),
																								   name(name),
																								   declared(false),
																								   intValue(intv),
																								   realValue(doublev),
																								   stringValue(stringv) {}
	Identifier(Identifier const& other): type(other.type), name(other.name), declared(other.declared), intValue(other.intValue),
										 realValue(other.realValue), stringValue(other.stringValue) {}


	void ChangeType(IdentType type)
	{
		this->type = type;
	}

	String const& GetName() const
	{
		return name;
	}

	void ChangeIntValue(int v)
	{
		intValue = v;
	}

	void ChangeRealValue(double v)
	{
		realValue = v;
	}

	void ChangeStringValue(String const& str)
	{
		stringValue = str;
	}

	void ChangeName(String const& newName)
	{
		name = newName;
	}

	IdentType GetType() const
	{
		return type;
	}

	int GetIntValue() const
	{
		return intValue;
	}

	double GetRealValue() const
	{
		return realValue;
	}

	String const& GetStringValue() const
	{
		return stringValue;
	}

	void Declare()
	{
		declared = true;
	}

	bool IsDeclared() const
	{
		return declared;
	}
};

/**************************************************/


/**************************************************/

class LexemeTable
{
	Lexeme* ptr;
	int size;
	int bufSize;

public:

	LexemeTable() : ptr(new Lexeme[BUF_SIZE]), size(0), bufSize(BUF_SIZE) {}
	LexemeTable(Lexeme const& lex)
	{
		bufSize = BUF_SIZE;
		size = 1;
		ptr = new Lexeme[bufSize];
		*ptr = lex;
	}
	LexemeTable(int size) : size(0), bufSize(size)
	{
		ptr = new Lexeme[size];
	}

	LexemeTable(LexemeTable const& other)
	{
		bufSize = other.bufSize;
		size = other.size;
		ptr = new Lexeme[bufSize];
		for(int i = 0; i < size; ++i)
			ptr[i] = other.ptr[i];
	}

	~LexemeTable()
	{
		delete[] ptr;
	}

	LexemeTable& operator=(LexemeTable const& other)
	{
		if(this != &other)
		{
			bufSize = other.bufSize;
			size = other.size;
			delete[] ptr;
			ptr = new Lexeme[bufSize];
			for(int i = 0; i < size; ++i)
				ptr[i] = other.ptr[i];
		}
		return (*this);
	}

	void Push(Lexeme const& lex)
	{
		if (ptr == nullptr)
		{
			size = 1;
			bufSize = BUF_SIZE;
			ptr = new Lexeme[bufSize];
			*ptr = lex;
		}
		else
		{
			if(size == bufSize)
			{
				Lexeme *temp = new Lexeme[size + 1];
				for (int i = 0; i < size; ++i)
				{
					temp[i] = ptr[i];
				}
				temp[size++] = lex;
				delete[] ptr;
				ptr = temp;
			}
			else
			{
				ptr[size++] = lex;
			}
		}
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

/**************************************************/

/**************************************************/

class IdentTable
{
	Identifier* ptr;
	int size;
	int bufSize;

public:

	IdentTable() : size(0), bufSize(BUF_SIZE), ptr(new Identifier[BUF_SIZE]) {}
	IdentTable(Identifier const& ident)
	{
		size = 1;
		bufSize = BUF_SIZE;
		ptr = new Identifier[bufSize];
		*ptr = ident;
	}
	IdentTable(int size) : size(0), bufSize(size)
	{
		ptr = new Identifier[bufSize];
	}

	IdentTable(IdentTable const& other)
	{
		if(other.ptr != nullptr)
		{
			size = other.size;
			bufSize = other.bufSize;
			ptr = new Identifier[bufSize];
			for (int i = 0; i < size; ++i)
				ptr[i] = other.ptr[i];
		}
		else
		{
			size = 0;
			ptr = nullptr;
		}
	}

	~IdentTable()
	{
		delete[] ptr;
	}

	IdentTable& operator=(IdentTable const& other)
	{
		if(this != &other)
		{
			if(ptr != nullptr)
			{
				delete[] ptr;
				size = other.size;
				bufSize = other.bufSize;
				ptr = new Identifier[bufSize];
				for (auto i = 0; i < size; ++i)
					ptr[i] = other.ptr[i];
			}
			else
			{
				size = 0;
				bufSize = BUF_SIZE;
				ptr = new Identifier[bufSize];
			}

		}
		return (*this);
	}

	void Push(Identifier const& ident)
	{
		if (ptr == nullptr)
		{
			size = 1;
			bufSize = BUF_SIZE;
			ptr = new Identifier[bufSize];
			*ptr = ident;
		}
		else
		{
			if(size == bufSize)
			{
				bufSize *= 2;
				Identifier *temp = new Identifier[bufSize];
				for (int i = 0; i < size; ++i)
				{
					temp[i] = ptr[i];
				}
				temp[size++] = ident;
				delete[] ptr;
				ptr = temp;
			}
			else
			{
				ptr[size++] = ident;
			}
		}
	}

	Identifier& operator[](int i)
	{
		return ptr[i];
	}
	
	Identifier const& operator[](int i) const
	{
		return ptr[i];
	}

	int Search(String const& string) const
	{
		for (int i = 0; i < size; ++i)
		{
			if (ptr[i].GetName() == string)
			{
				return i;
			}
		}
		return -1;
	}

	int GetSize() const
	{
		return size;
	}

	void Pop()
	{
		--size;
	}

};

/**************************************************/

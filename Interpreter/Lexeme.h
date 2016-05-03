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

	LEXEME_END
};

/**************************************************/

class Lexeme
{
	LexemeType type;
	int value;

public:

	Lexeme(LexemeType type = LEXEME_VOID, int value = 0) : type(type), value(value)
	{ }

	void Change(LexemeType type = LEXEME_VOID, int value = 0, bool declared = false)
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
	}

	bool operator==(Lexeme const &other) const
	{
		return ((type == other.type) && (value == other.value));
	}

	bool operator!= (Lexeme const &other) const
	{
		return ((type != other.type) || (value != other.value));
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
			if(size == 1)
				delete ptr;
			else
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

/**************************************************/

/**************************************************/

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

	IdentTable(IdentTable const& other)
	{
		size = other.size;
		ptr = new Identifier[size];
		for (int i = 0; i < size; ++i)
			ptr[i] = other.ptr[i];
	}

	~IdentTable()
	{
		if(size == 1)
			delete ptr;
		else
			delete[] ptr;
	}

	IdentTable& operator=(IdentTable const& other)
	{
		if(this != &other)
		{
			if (size == 1)
				delete ptr;
			else
				delete[] ptr;
			size = other.size;
			ptr = new Identifier[size];
			for (auto i = 0; i < size; ++i)
				ptr[i] = other.ptr[i];

		}
		return (*this);
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
			if(size == 1)
				delete ptr;
			else
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

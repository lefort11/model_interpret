#include <iostream>

using namespace std;

enum LexemeType
{
	LEXEME_VOID,
	LEXEME_PROGRAM,
	LEXEME_INT,
	LEXEME_STRING,
	LEXEME_REAL,
	LEXEME_STRUCT,

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
	LEXEME_MULTIPLE,
	LEXEME_DIVISION,
	LEXEME_LESS,
	LEXEME_MORE,
	LEXEME_LESS_OR_EQUAL,
	LEXEME_MORE_OR_EQUAL,
	LEXEME_EQUAL,
	LEXEME_NOT_EQUAL,
	LEXEME_ASSIGNMENT,

	LEXEME_COMMA,
	LEXEME_LBRACKET,
	LEXEME_RBRACKET,
	LEXEME_LPARENTH,
	LEXEME_RPARENTH,
	LEXEME_SEMICOLON,
	LEXEME_COLON,
	LEXEME_APOSTROPHE,
	LEXEME_QUOTE
};

class Lexeme
{
	LexemeType type;
	int value;

public:

	Lexeme(LexemeType type = LEXEME_VOID, int value = 0) : type(type), value(value) {}

	void Change(LexemeType type = LEXEME_VOID, int value = 0)
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
};

class Scanner
{
	enum State
	{
		STATE_START,
		STATE_IDENTIFIER,
		STATE_KEYWORD,
		STATE_DELIMITER
	};

	static const char* WordTable[];
	static const char* DelimiterTable[];
};

const char* Scanner::WordTable[] =
		{
				"",
				"program",
				"int",
				"string",
				"real",
				"struct",

				"if",
				"else",
				"for",
				"while",
				"break",
				"goto",
				"read",
				"write",

				"not",
				"and",
				"or",
				nullptr
		};

const char* Scanner::DelimiterTable[]=
		{
				"",
				"+",
				"-",
				"*",
				"/",
				";",
				"(",
				")",
				"{",
				"}",
				",",
				">",
				"<",
				"<=",
				">=",
				"==",
				"!=",
				"=",
				":",
				"'",
				"""",
				nullptr
		};
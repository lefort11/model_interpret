#include <iostream>

using namespace std;

enum LexemeType
{
	LEXEME_VOID,
	LEXEME_KEYWORD,
	LEXEME_IDENTIFIER,
	LEXEME_CONSTANT,
	LEXEME_OPERATOR, //Arithmetic and logical operators
	LEXEME_DELIMITER,
	LEXEME_END
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
		STATE_OPERATOR,
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

	"if",
	"for",
	"while",
	"break",
	"goto",
	"read",
	"write",

	"not",
	"and",
	"or",
};

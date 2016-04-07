#include <iostream>
#include "Lexeme.h"
#include <cstdio>
#include <cctype>


using namespace std;



class Scanner
{
	enum State
	{
		STATE_START,
		STATE_NAME,
		STATE_CONSTANT,
		STATE_REAL_CONST,
		STATE_STRING_CONST,
		STATE_KEYWORD,
		STATE_DELIMITER,
		STATE_COMMENT,
		STATE_ERROR,
		//STATE_END
	};

	static const char* WordTable[];
	static const char* DelimiterTable[];
	static const LexemeType LexemeWords[];
	static const LexemeType LexemeDelimeters[];

	static LexemeTable lexemeTable;
	static IdentTable identTable;

	FILE* file;
	State state;
	char c;
	String buf;
	int lastIdent;
public:


	Scanner(const char* filepath) : file(fopen(filepath, "r")), state(STATE_START), c(0), buf(10, 0), lastIdent(0) {}

	static LexemeType IsDelimiter(const char* word);

	static LexemeType IsReserved(const char* word);

	char GetChar() const
	{
		return fgetc(file);
	}

	Lexeme GetLexeme(); // this method fills ident table and returns lexems

	void MakeLexemeTable();

};



LexemeTable Scanner::lexemeTable = LexemeTable();

IdentTable Scanner::identTable = IdentTable();

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

const char* Scanner::DelimiterTable[] =
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
	".",
	nullptr
};

const LexemeType Scanner::LexemeWords[] =
{
	LEXEME_VOID, //0
	LEXEME_PROGRAM,
	LEXEME_INT,
	LEXEME_STRING,
	LEXEME_REAL,
	LEXEME_STRUCT,
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
	LEXEME_VOID
};

const LexemeType Scanner::LexemeDelimeters[] =
{
	LEXEME_VOID,
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
	LEXEME_VOID
};



LexemeType Scanner::IsReserved(const char* word)
{
	int i = 1;
	while(WordTable[i] != nullptr)
	{
		strcmp(word, WordTable[i]);
		++i;
	}
	return LexemeWords[i];
}

LexemeType Scanner::IsDelimiter(const char* word)
{
	int i = 1;
	while(DelimiterTable[i] !=  nullptr)
	{
		strcmp(word, DelimiterTable[i]);
		++i;
	}
	return LexemeDelimeters[i];
}



Lexeme Scanner::GetLexeme()
{
	while (true)
	{
		switch (state)
		{
		case STATE_START:
			if (isalpha(c))
			{
				state = STATE_KEYWORD;
				buf += c;
				c = GetChar();
			}
			else if (isdigit(c))
			{
				state = STATE_CONSTANT;
				buf += c;
				c = GetChar();
			}
			else if (c == '"')
			{
				state = STATE_STRING_CONST;
				c = GetChar();
			}
			else if (c == '{')
			{
				state = STATE_DELIMITER;
				return Lexeme(LEXEME_LPARENTH, 0);
			}
			else
				state = STATE_ERROR;
			break;

		case STATE_CONSTANT:
			if (c == '.')
			{
				state = STATE_REAL_CONST;
				buf += c;
				c = GetChar();
			}
			else if (isdigit(c))
			{
				buf += c;
				c = GetChar();
			}
			else
			{
				state = STATE_DELIMITER;
				//Don't know should i to put const to ident table or not
				//I think yes
				Identifier id(INT_CONST, nullptr, atoi(buf), 0, nullptr);
				identTable.Push(id);
				return Lexeme(LEXEME_INT_CONST, lastIdent++);
			}
			break;

		case STATE_REAL_CONST:
			if (c == '.')
				state = STATE_ERROR;
			else if (isdigit(c))
			{
				buf += c;
				c = GetChar();
			}
			else
			{
				state = STATE_DELIMITER;
				Identifier id(REAL_CONST, nullptr, 0, atol(buf), nullptr);
				identTable.Push(id);
				return Lexeme(LEXEME_REAL_CONST, lastIdent++);
			}
			break;

		case STATE_STRING_CONST:
			if (c != '"')
			{
				buf += c;
				c = GetChar();
			}
			else
			{
				c = GetChar();
				state = STATE_START;
				Identifier id(STRING_CONST, nullptr, 0, 0, buf);
				identTable.Push(id);
				return Lexeme(LEXEME_STRING_CONST, lastIdent++);
			}
			break;

		case STATE_KEYWORD:
			if(isdigit(c))
			{
				state = STATE_NAME;
				buf += c;
				c = GetChar();
			}
			else if(isalpha(c))
			{
				buf += c;
				c = GetChar();
			}
			else
			{
				state = STATE_DELIMITER;
				LexemeType type = IsReserved(buf);
				if(type != LEXEME_VOID) // it is a reserved word
					return Lexeme(type, 0);
				// it is an identifier
				Identifier id(VOID, buf, 0, 0, nullptr);
				identTable.Push(id);
				return Lexeme(LEXEME_NAME, lastIdent++);
			}
			break;

		case STATE_NAME:
			if (isdigit(c)) //here i may come only after getting digets
			{
				buf += c;
				c = GetChar();
			}
			else if (isalpha(c)) //incorrect
				state = STATE_ERROR;
			else
			{
				state = STATE_DELIMITER;
				Identifier id(VOID, buf, 0, 0, nullptr);
				identTable.Push(id);
				return Lexeme(LEXEME_NAME, lastIdent++);
			}
			break;

		case STATE_DELIMITER:
			if (c == EOF)
				return Lexeme(LEXEME_END, 0);
			if(c == '/')
			{
				c = GetChar();
				if(c == '*')
				{
					c = GetChar();
					state = STATE_COMMENT;
				}
				else
				{
					state = STATE_START;
					return Lexeme(LEXEME_DIVISION, 0);
				}
			}
			if ((c == ' ') || isalpha(c) || isdigit(c) || (c == '"') || (c == '\n') || (c == '\r'))
			{
				if ((c == ' ') || c == '\n')
				{
					while ((c == ' ') || c == '\n')
						c = GetChar();
					state = STATE_START;
				}
				else if (isalpha(c))
					state = STATE_KEYWORD;
				else if (isdigit(c))
					state = STATE_CONSTANT;
				else if (c == '"')
				{
					c = GetChar();
					state = STATE_STRING_CONST;
				}
				else if (c == '\r')
					c = GetChar(); // will be '\n' next
				LexemeType type = IsDelimiter(buf);
				if (type == LEXEME_VOID)
					state = STATE_ERROR;
				else
				{
					return Lexeme(type, 0);
				}
			}
			else
			{
				buf += c;
				c = GetChar();
			}
			break;

		case STATE_COMMENT:
			while (c != '*')
				c = GetChar();
			if (c == '/')
			{
				c = GetChar();
				state = STATE_START;
			}
			break;

		case STATE_ERROR:
			throw 1;
		}
	}
}


void Scanner::MakeLexemeTable()
{
	c = GetChar();
	while(c != EOF)
	{
		buf.Clear();
		lexemeTable.Push(GetLexeme());
	}
}

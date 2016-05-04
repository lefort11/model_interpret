#include "Scanner.h"

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
	"\"",
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

const LexemeType Scanner::LexemeDelimiters[] =
{
	LEXEME_VOID,
	LEXEME_PLUS,
	LEXEME_MINUS,
	LEXEME_MULTIPLY,
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


//IdentTable Scanner::identTable = IdentTable();

std::vector<Scanner::Structure> Scanner::structuresVector;

Lexeme Scanner::GetLexeme()
{
	while (c != EOF)
	{
		switch (state)
		{
			case STATE_START:
				GetChar();
				state = STATE_UNCERTAINTY;
				break;

			case STATE_UNCERTAINTY:
				if (isalpha(c))
				{
					state = STATE_KEYWORD;
					buf += c;
					GetChar();
				}
				else if (isdigit(c)) // || c == '+' || '-' ??
				{
					state = STATE_CONSTANT;
					buf += c;
					GetChar();
				}
				else if (c == '"')
				{
					state = STATE_STRING_CONST;
					GetChar();
				}
				else
				{
					state = STATE_DELIMITER;
				}
				break;


			case STATE_CONSTANT:
				if (c == '.')
				{
					state = STATE_REAL_CONST;
					buf += c;
					GetChar();
				}
				else if (isdigit(c))
				{
					buf += c;
					GetChar();
				}
				else
				{
					state = STATE_DELIMITER;
					//Don't know should i to put const to ident table or not
					//I think yes
					Identifier id(INT_CONST, nullptr, atoi(buf.GetPtr()), 0, nullptr);
					//identTable.Push(id);
					structuresVector[0].Push(id);
					buf.Clear();
					return Lexeme(LEXEME_INT_CONST, lastIdent++);
				}
				break;

			case STATE_REAL_CONST:
				if (c == '.')
					state = STATE_ERROR;
				else if (isdigit(c))
				{
					buf += c;
					GetChar();
				}
				else
				{
					state = STATE_DELIMITER;
					Identifier id(REAL_CONST, nullptr, 0, atof(buf.GetPtr()), nullptr);
					//identTable.Push(id);
					structuresVector[0].Push(id);
					buf.Clear();
					return Lexeme(LEXEME_REAL_CONST, lastIdent++);
				}
				break;

			case STATE_STRING_CONST:
				if (c != '"')
				{
					buf += c;
					GetChar();
				}
				else
				{
					GetChar();
					state = STATE_UNCERTAINTY;
					Identifier id(STRING_CONST, nullptr, 0, 0, buf);
					//identTable.Push(id);
					structuresVector[0].Push(id);
					buf.Clear();
					return Lexeme(LEXEME_STRING_CONST, lastIdent++);
				}
				break;

			case STATE_KEYWORD:
				if (isdigit(c))
				{
					state = STATE_NAME;
					buf += c;
					GetChar();
				}
				else if (isalpha(c))
				{
					buf += c;
					GetChar();
				}
				else
				{
					state = STATE_DELIMITER;
					LexemeType type = IsReserved(buf);
					if (type != LEXEME_VOID) // it is a reserved word
					{
						buf.Clear();
						return Lexeme(type, 0);
					}
					// it is an identifier
					int pos;
					if ((pos = structuresVector[0].Search(buf)) == -1) // not found
					{
						Identifier id(VOID, buf, 0, 0, nullptr);
						structuresVector[0].Push(id);
						buf.Clear();
						return Lexeme(LEXEME_NAME, lastIdent++);
					}
					//return Lexeme(LEXEME_NAME, pos); //this should be corrected for Preprocessing
					if (structuresVector[0][pos].GetType() == INT_CONST) //this name can be a defined name of some int constant
					{
						buf.Clear();
						return Lexeme(LEXEME_INT_CONST, pos);
					}
					buf.Clear();
					return Lexeme(LEXEME_NAME, pos);
				}
				break;

			case STATE_NAME:
				if (isdigit(c)) //here i may come only after getting digits
				{
					buf += c;
					GetChar();
				}
				else if (isalpha(c)) //incorrect
					state = STATE_ERROR;
				else
				{
					state = STATE_DELIMITER;
					Identifier id(VOID, buf, 0, 0, nullptr);
					//identTable.Push(id);
					structuresVector[0].Push(id);
					buf.Clear();
					return Lexeme(LEXEME_NAME, lastIdent++);
				}
				break;

			case STATE_DELIMITER:
				if (c == EOF)
					return Lexeme(LEXEME_END, 0);
				if (c == '/')
				{
					GetChar();
					if (c == '*')
					{
						GetChar();
						state = STATE_COMMENT;
					}
					else
					{
						state = STATE_UNCERTAINTY;
						buf.Clear();
						return Lexeme(LEXEME_DIVISION, 0);
					}
				}
				else if ((c == ' ') || isalpha(c) || isdigit(c) || (c == '"') || (c == '\n') ||
						(c == '\r') || (c == '\t') || (c == ';') || (c == ')') || (c == '(') || (c == '}') || (c == '{')) //getting of delimiter ended
				{
					/* в эту ветку можно попасть по двум причинам:
					 * либо найден разделитель разделителей (закончено чтение разделителя)
					 * либо закончено чтение чего либо другого
					 * на случай конца чтения разделителя и нужна следующая ветка */
					if (!buf.IsEmpty()) //if there was a delimiter
					{
						LexemeType type = IsDelimiter(buf);
						if (type == LEXEME_VOID)
							state = STATE_ERROR;
						else
						{
							// !!!
							buf.Clear();
							return Lexeme(type, 0);
						}
					}
					if ((c == ' ') || (c == '\n') || (c == '\t'))
					{
						while ((c == ' ') || (c == '\n') || (c == '\t'))
							GetChar();
						state = STATE_UNCERTAINTY;
					}
					else if (isalpha(c))
						state = STATE_KEYWORD;
					else if (isdigit(c))
						state = STATE_CONSTANT;
					else if (c == '"')
					{
						GetChar();
						state = STATE_STRING_CONST;
					}
					else if (c == '\r')
						GetChar(); //'\n' will be next
					else if (c == '(')
					{
						state = STATE_UNCERTAINTY;
						buf.Clear();
						GetChar();
						return Lexeme(LEXEME_LBRACKET);
					}
					else if (c == ')')
					{
						state = STATE_UNCERTAINTY;
						buf.Clear();
						GetChar();
						return Lexeme(LEXEME_RBRACKET);
					}
					else if(c == '}')
					{
						state = STATE_UNCERTAINTY;
						buf.Clear();
						GetChar();
						return Lexeme(LEXEME_RPARENTH);
					}
					else if(c == '{')
					{
						state = STATE_UNCERTAINTY;
						buf.Clear();
						GetChar();
						return Lexeme(LEXEME_LPARENTH);
					}

					else // c == ';'
					{
						state = STATE_UNCERTAINTY;
						buf.Clear();
						GetChar();
						return Lexeme(LEXEME_SEMICOLON, 0);

					}
				}
				else if (c == '#')
				{
					state = STATE_PREPROCESSOR;
				}
				else
				{
					buf += c;
					GetChar();
				}
				break;

			case STATE_COMMENT:
				while ((c != '*') && (c != EOF))
					GetChar();
				if (c == EOF)
					state = STATE_ERROR;
				GetChar();
				if (c == '/')
				{
					GetChar();
					state = STATE_UNCERTAINTY;
				}
				else if (c == EOF)
					state = STATE_ERROR;
				break;

			case STATE_PREPROCESSOR:
				state = STATE_UNCERTAINTY;
				c = PP.Handler(file, structuresVector[0].GetTableReference(), lastIdent); //after PP handling last read char was '\n' || EOF !!!!
															 //Mb i should return f.e. -1 if the EOF was reached to prevent errors
															 // but if there is ' ' or '\n' before EOF (if an empty string at the end of text file) then it will be ok.
															 //GetChar();
				break;

			case STATE_ERROR:
				throw ScannerException();
		}
	}
	return Lexeme(LEXEME_END, 0);
}
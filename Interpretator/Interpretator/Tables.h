#pragma once

#include "Scanner.cpp"

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
	LEXEME_VOID
};

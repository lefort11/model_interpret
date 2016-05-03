#pragma once

#include <iostream>
#include "Lexeme.h"
#include "Preprocessor.h"
#include <cctype>

using namespace std;



class Scanner
{
	enum State
	{
		STATE_START, // STart was replaced by uncertainty...
		STATE_UNCERTAINTY, // check it later
		STATE_NAME,
		STATE_CONSTANT,
		STATE_REAL_CONST,
		STATE_STRING_CONST,
		STATE_KEYWORD,
		STATE_DELIMITER,
		STATE_COMMENT,
		STATE_ERROR,
		STATE_PREPROCESSOR,
		//STATE_END
	};

	static const char* WordTable[];
	static const char* DelimiterTable[];
	static const LexemeType LexemeWords[];
	static const LexemeType LexemeDelimiters[];



	FILE* file;
	State state;
	int c;
	String buf;
	int lastIdent;
	Preprocessor PP;

public:

	LexemeTable lexemeTable;
	static IdentTable identTable;

	class ScannerException {};

	Scanner(const char* filepath) : file(fopen(filepath, "r")), state(STATE_START), c(0), buf(20, 0), lastIdent(0), PP()
	{
		if(file == nullptr)
		{
			throw ScannerException();
		}
	}

	static LexemeType IsDelimiter(String const& word)
	{
		int i = 1;
		while (DelimiterTable[i] != nullptr)
		{
			if (word == DelimiterTable[i])
				return LexemeDelimiters[i];
			++i;
		}
		return LEXEME_VOID;
	}

	static LexemeType IsReserved(String const& word)
	{
		int i = 1;
		while (WordTable[i] != nullptr)
		{
			if (word == WordTable[i])
				return LexemeWords[i];
			++i;
		}
		return LEXEME_VOID;
	}

	int GetChar()
	{
		return c = fgetc(file);
	}

	Lexeme GetLexeme(); // this method fills ident table and returns lexems

	void MakeLexemeTable()
	{
		while (c != EOF)
		{
			lexemeTable.Push(GetLexeme());
		}
		if (PP.GetIfNumber() != 0)
		{
			throw Preprocessor::PPException();
		}
	}

};




#include <iostream>
#include "Lexeme.h"
#include <vector>

using namespace std;


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
	static const LexemeType LexemeWords[];
	static const LexemeType LexemeDelimeters[];
	FILE* file;
	State ScannerState;
public:


	Scanner(const char* filepath) : ScannerState(STATE_START)
	{
		file = fopen(filepath, "r");
	}

	static LexemeType IsDelimeter(const char* word); 

	static LexemeType IsReserved(const char* word);

	Lexeme GetLexeme() const;

	vector<Lexeme> MakeLexVector() const;


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

LexemeType Scanner::IsDelimeter(const char* word)
{
	int i = 1;
	while(DelimiterTable[i] !=  nullptr)
	{
		strcmp(word, DelimiterTable[i]);
		++i;
	}
	return LexemeDelimeters[i];
}
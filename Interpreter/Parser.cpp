#include "Parser.h"


void Parser::Analyze()
{
	if(scanner.lexemeTable[lastLexeme] == LEXEME_PROGRAM)
	{
		++lastLexeme;
		Program();
		if(scanner.lexemeTable[lastLexeme] != LEXEME_END)
			throw ParserException();
	}
	else
		throw ParserException();
}



void Parser::Program()
{
	if(scanner.lexemeTable[lastLexeme] == LEXEME_LPARENTH)
	{
		++lastLexeme;
		Descriptions();
		Operators();
		if(scanner.lexemeTable[lastLexeme] != LEXEME_RPARENTH)
			throw ParserException();
	}
	else
		throw ParserException();
}


void Descriptions()
{

}
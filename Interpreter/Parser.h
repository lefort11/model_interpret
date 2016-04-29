#pragma once

#include <iostream>
#include "Scanner.h"
#include "String.h"


class Parser
{
	Scanner scanner;
	Lexeme currentLexeme;
	/*LexemeType currentLexemeType;
	int currentLexemeValue; */


	void Program();
	void Descriptions();
	void StructDescription();
	void VariableDescription();
	void Type();
	void Variable();
	void Constant();
	void Integer(); // integer constant
	void Real(); // integer constant
	void String(); // integer constant
	void Sign();
	void Operators();
	void SingleOperator();
	void CompoundOperator();
	void ExpressionOperator();
	void Expression();

public:

	class ParserException {};

	void GetLexeme()
	{
		currentLexeme = scanner.GetLexeme();
		//currentLexemeValue = currentLexeme.GetValue();
		//currentLexemeType = currentLexeme.GetType();
	}

	Parser(const char* filepath) : scanner(filepath), currentLexeme(LEXEME_VOID)
	{}

	void Analyze();

};
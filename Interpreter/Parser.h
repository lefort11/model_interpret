#pragma once

#include <iostream>
#include "Scanner.h"
#include "String.h"


class Parser
{
	Scanner scanner;
	int lastLexeme; // last lexeme number in lexemeTable

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

	Parser(const char* filepath): scanner(filepath), lastLexeme(0)
	{
		scanner.MakeLexemeTable();
	}

	void Analyze();

};
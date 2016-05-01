#pragma once

#include <iostream>
#include "Scanner.h"
#include <vector>


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
	void StructureMemberDescription();
	//void Type();
	//void Variable();
	//void Constant();
	//void Integer(); // integer constant
	//void Real(); // integer constant
	//void String(); // integer constant
	//void Sign();
	void Operators();
	void SingleOperator();
	//void CompoundOperator();
	//void ExpressionOperator();
	void Expression();
	void ArithmeticExpression();
	void Summand();
	void Factor();
	//void Variable();
	void AssignmentExpression();
	int lastStructureNumber;
	void GetLexeme()
	{
		currentLexeme = scanner.GetLexeme();
		//currentLexemeValue = currentLexeme.GetValue();
		//currentLexemeType = currentLexeme.GetType();
	}

public:

	vector<IdentTable> structuresVector;

	class ParserException {};



	Parser(const char* filepath) : scanner(filepath), currentLexeme(LEXEME_VOID), lastStructureNumber(0)
	{}

	bool isOperator() const
	{
		return true;
		//return ((currentLexeme == LEXEME_IF) || (currentLexeme == LEXEME_WHILE) || (currentLexeme == LEXEME_FOR) || (currentLexeme == LEXEME_BREAK) || (currentLexeme == LEXEME_GOTO) || (currentLexeme == LEXEME_READ) || (currentLexeme == LEXEME_WRITE) || isCompoundOperator() || isMarkedOperator() || isExpressOperator());
	}


	void Analyze();

};
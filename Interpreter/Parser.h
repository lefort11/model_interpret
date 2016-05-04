#pragma once

#include <iostream>
#include "Scanner.h"
#include <vector>
#include "ReversePolishNotation.h"
#include "Stack.h"


class Parser
{
	Scanner scanner;
	Lexeme currentLexeme;
	Stack <LexemeType> lexemeStack;
	LexemeTable labelTable;

	int lastLabel;



	void Program();
	void Descriptions();
	void StructDescription();
	void VariableDescription();
	void StructureMemberDescription();
	void Operators();
	void SingleOperator();
	void Expression();
	void ArithmeticExpression();
	void Summand();
	void Factor();
	void AssignmentExpression();

	int isLoop;

	void GetLexeme()
	{
		currentLexeme = scanner.GetLexeme();
		//currentLexemeValue = currentLexeme.GetValue();
		//currentLexemeType = currentLexeme.GetType()
	}

	void CheckOperands();

	void CheckNotOperand();
	void CheckUnaryMinusOperand();

public:

	ReversePolishNotation program; //pshe pshe pshe

	class ParserException {};

	

	int lastStructureNumber;


	Parser(const char* filepath) : scanner(filepath), currentLexeme(LEXEME_VOID), isLoop(0), program(1000), lexemeStack(100), lastStructureNumber(0)
	{}



	void Analyze();

};
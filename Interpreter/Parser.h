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

	int lastStructureNumber;
	void GetLexeme()
	{
		currentLexeme = scanner.GetLexeme();
		//currentLexemeValue = currentLexeme.GetValue();
		//currentLexemeType = currentLexeme.GetType();
	}

	void CheckOperands();

	void CheckNotOperand();
	void CheckUnaryMinusOperand();

public:

	vector<IdentTable> structuresVector;
	ReversePolishNotation program; //pshe pshe pshe

	class ParserException {};



	Parser(const char* filepath) : scanner(filepath), currentLexeme(LEXEME_VOID), lastStructureNumber(0), isLoop(0), program(1000), lexemeStack(100)
	{}



	void Analyze();

};
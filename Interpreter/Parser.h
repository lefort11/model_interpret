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
		//currentLexemeType = currentLexeme.GetType();
	}

	void CheckOperands();

	void CheckNotOperand();
	void CheckUnaryMinusOperand();

public:

	ReversePolishNotation program; //pshe pshe pshe

	class ParserException {};

	class Structure
	{
		IdentTable identTable;
		String nameType;

	public:
		Structure(String name) :identTable(), nameType(name) {}

		void Push(Identifier ident)
		{
			identTable.Push(ident);
		}

		int GetSize() const
		{
			return identTable.GetSize();
		}

		String const& GetTypeName() const
		{
			return nameType;
		}

		Identifier const& operator[] (int i) const
		{
			return identTable[i];
		}

		Identifier& operator[] (int i) 
		{
			return identTable[i];
		}

		int Search(String name) const
		{
			return identTable.Search(name);
		}

	};

	static vector<Structure> structuresVector;
	static int lastStructureNumber;



	Parser(const char* filepath) : scanner(filepath), currentLexeme(LEXEME_VOID), isLoop(0), program(1000), lexemeStack(100)
	{}



	void Analyze();

};
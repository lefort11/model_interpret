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

	class Structure
	{
		IdentTable identTable;
		String nameType;

	public:
		Structure(String name): identTable(), nameType(name) {}
		Structure(IdentTable idTable, String name): identTable(idTable), nameType(name) {}

		Structure(Structure const& other): identTable(other.identTable), nameType(other.nameType)
		{ }

		void Push(Identifier const& ident)
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

		int Search(String const& name) const
		{
			return identTable.Search(name);
		}

		Structure& operator= (Structure const& other)
		{
			if(this != &other)
			{
				identTable = other.identTable;
				nameType = other.nameType;
			}
			return (*this);
		}

	};

	static std::vector<Structure> structuresVector;
	int lastStructureNumber;


	Parser(const char* filepath) : scanner(filepath), currentLexeme(LEXEME_VOID), isLoop(0), program(1000), lexemeStack(100), lastStructureNumber(0)
	{}



	void Analyze();

};
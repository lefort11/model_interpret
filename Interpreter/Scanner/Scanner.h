#pragma once

#include <iostream>
#include "../Lexeme.h"
#include "preprocessor.h"
#include <vector>

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
	//static IdentTable identTable;

	class ScannerException {};

	class Structure
	{
		IdentTable identTable;
		String nameType;

	public:
		Structure(String name) : identTable(), nameType(name) {}
		Structure(IdentTable idTable, String name) : identTable(idTable), nameType(name) {}

		Structure(Structure const& other) : identTable(other.identTable), nameType(other.nameType)
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
			if (this != &other)
			{
				identTable = other.identTable;
				nameType = other.nameType;
			}
			return (*this);
		}

		IdentTable& GetTableReference()
		{
			return identTable;
		}

	};

	static std::vector<Structure> structuresVector;

	Scanner(const char* filepath) : file(fopen(filepath, "r")), state(STATE_START), c(0), buf(20, 0), lastIdent(0), PP()
	{
		if(file == nullptr)
		{
			throw ScannerException();
		}
		structuresVector.push_back(Structure(nullptr));
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

	void IncLastIdentNumber()
	{
		++lastIdent;
	}

};




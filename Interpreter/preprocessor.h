#pragma once

#include "String.h"
#include "Lexeme.h"
#include <list>
#include <iostream>
#include <cctype>


enum PPLexemeType
{
	PP_VOID,
	PP_DEFINE,
	PP_UNDEF,
	PP_IFDEF,
	PP_IFNDEF,
	PP_ELSE,
	PP_ENDIF
};

class Preprocessor
{

	static const PPLexemeType PPLexemes[];
	static const char* PPWords[];


	list<String> defined;

	static int ifNumber;

	int c;
	String buf;

public:
	Preprocessor() : c(0), buf(10, 0) {}

	class PPException{};

	static int GetIfNumber()
	{
		return ifNumber;
	}

	static PPLexemeType IsPPWord(String const& word)
	{
		int i = 1;
		while (PPWords[i] != nullptr)
		{
			if (word == PPWords[i])
			{
				return PPLexemes[i];
			}
			++i;
		}
		return PP_VOID;
	}


	int Handler(FILE* f, IdentTable& identTable, int& lastIdent); //return int here?

	void GetDirective(FILE* f)
	{
		buf.Clear();
		c = fgetc(f);
		while ((c != ' ') && (c != '\n') && (c != '\r') && (c != EOF))
		{
			buf += c;
			c = fgetc(f);
		}
	}

	void ReadIdent(FILE* f)
	{
		while (c == ' ')
			c = fgetc(f);
		buf.Clear();
		while (isalpha(c)) //check this later
		{
			buf += c;
			c = fgetc(f);
		}
		//now digits are coming
		if (buf.IsEmpty())
		{
			PPException ppExcpt;
			throw ppExcpt;
		}
		while (isdigit(c)) // check this later
		{
			buf += c;
			c = fgetc(f);
		}
		if ((c != ' ') && (c != '\n') && (c != '\r') && (c != EOF))
			throw PPException();
		if (c == '\r')
			c = fgetc(f);
	}
	
	int ReadNumb(FILE* f)
	{
		while (c == ' ')
			c = fgetc(f);
		String buf(10, 0);
		if (c == '-')
		{
			buf += c;
			c = fgetc(f);
		}
		else if (c == '+')
			c = fgetc(f);
		while (isdigit(c))
		{
			buf += c;
			c = fgetc(f);
		}
		if (buf.IsEmpty())
		{
			PPException ppExcept;
			throw ppExcept;
		}
		return atoi(buf.GetPtr());
	}


	list<String>::iterator IsDefined(String name)
	{
		list<String>::iterator it = defined.begin();
		while ((it != defined.end()) && ((*it) != name))
			++it;
		return it;
	}

};

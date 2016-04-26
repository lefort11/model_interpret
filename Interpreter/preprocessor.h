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
	/*enum PPState
	{
		//PP_START,
		PP_KEYWORD,
		PP_NAME,
		PP_HANDLER
	};*/

	static const PPLexemeType PPLexemes[];
	static const char* PPWords[];


	list<String> defined;

	static int ifNumber;

	int c;
	String buf;

public:
	class PPException{};

	static int GetIfNumber()
	{
		return ifNumber;
	}

	static PPLexemeType IsPPWord(String const& word);

	Preprocessor() : c(0), buf(10, 0) {}

	int Handler(FILE* f, IdentTable& identTable, int& lastIdent); //return int here?

	void GetDirective(FILE* f);

	void ReadIdent(FILE* f);
	
	int ReadNumb(FILE* f);

	list<String>::iterator IsDefined(String name);

};


inline list<String>::iterator Preprocessor::IsDefined(String name)
{
	list<String>::iterator it = defined.begin();
	while( (it != defined.end()) && ((*it) != name))
		++it;
	return it;
}


const PPLexemeType Preprocessor::PPLexemes[] =
{
	PP_VOID,
	PP_DEFINE,
	PP_UNDEF,
	PP_IFDEF,
	PP_IFNDEF,
	PP_ELSE,
	PP_ENDIF,
	PP_VOID
};

const char* Preprocessor::PPWords[] =
{
	"",
	"define",
	"undef",
	"ifdef",
	"ifndef",
	"else",
	"endif",
	nullptr
};


inline PPLexemeType Preprocessor::IsPPWord(String const& word)
{
	int i = 1;
	while(PPWords[i] != nullptr)
	{
		if (word == PPWords[i])
		{
			return PPLexemes[i];
		}
		++i;
	}
	return PP_VOID;
}


inline void Preprocessor::GetDirective(FILE* f) 
{
	buf.Clear();
	c = fgetc(f);
	while((c != ' ') && (c != '\n') && (c != '\r') && (c != EOF))
	{
		buf += c;
		c = fgetc(f);
	}
}

inline void Preprocessor::ReadIdent(FILE* f)
{
	while (c == ' ')
		c = fgetc(f);
	buf.Clear();
	while((c != ' ') && (c != '\n') && (c != '\r') && (isalpha(c)) && (c != EOF))
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
	while(isdigit(c))
	{
		buf += c;
		c = fgetc(f);
	}
}


inline int Preprocessor::ReadNumb(FILE* f)
{
	while (c == ' ')
		c = fgetc(f);
	String buf(10, 0);
	while(isdigit(c))
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





inline int Preprocessor::Handler(FILE* f, IdentTable& identTable, int& lastIdent)
{
	// firstly a directive should be read
	GetDirective(f);
	int position;
	PPLexemeType type = IsPPWord(buf);
	list<String>::iterator it;
	int localIfNumber;
	switch(type)
	{
	case PP_VOID:
		throw PPException();

	case PP_DEFINE:
		//now identifier should be read
		//state = PP_NAME;
		//#define asd 213
		if (c != ' ')
			throw PPException();
		ReadIdent(f);
		position = identTable.Search(buf); // ~ IsDefined()
		if(position == -1)
		{
			Identifier id(INT_CONST, buf, ReadNumb(f), 0, nullptr);
			identTable.Push(id);
			++lastIdent;
		}
		else
		{
			identTable[position].ChangeIntValue(ReadNumb(f));
		}
		defined.push_back(buf);
		break;

	case PP_UNDEF:
		if (c != ' ')
			throw PPException();
		ReadIdent(f);
		it = IsDefined(buf);
		if (it == defined.end()) // not found => error
			throw PPException();
		defined.erase(it); //deleting from defined list
		position = identTable.Search(buf);
		identTable[position].ChangeName(nullptr); //renaming of named constant to make defining again possible
		break;

	case PP_IFDEF:
		localIfNumber = 1;
		++ifNumber;
		ReadIdent(f); // c = ' ' or '\n' after that
		if(IsDefined(buf) == defined.end())
		{
			while ((c != EOF) && (localIfNumber > 0))
			{
				c = fgetc(f);
				while (c != '#')
					c = fgetc(f);
				// # was found
				GetDirective(f);
				if ((buf == String("ifdef")) || (buf == String("ifndef")))
				{
					++ifNumber;
					++localIfNumber;
				}
				else if ((buf == String("endif")))
				{
					--ifNumber;
					--localIfNumber;
				}
				else if ((buf == String("else")) && (localIfNumber == 1))
					break;
				else
					throw PPException();

			}
		}
		break;


	case PP_IFNDEF:
		localIfNumber = 1;
		++ifNumber;
		ReadIdent(f); // c = ' ' or '\n' after that
		if (IsDefined(buf) != defined.end())
		{
			while ((c != EOF) && (localIfNumber > 0))
			{
				c = fgetc(f);
				while (c != '#')
					c = fgetc(f);
				// # was found
				GetDirective(f);
				if ((buf == "ifdef") || (buf == "ifndef"))
				{
					++ifNumber;
					++localIfNumber;
				}
				else if ((buf == "endif"))
				{
					--ifNumber;
					--localIfNumber;
				}
				else if ((buf == "else") && (localIfNumber == 1))
					break;
				else
					throw PPException();

			}
		}
		break;
		

	case PP_ENDIF:
		--ifNumber;
		if (ifNumber < 0)
			throw PPException();
		break;

	case PP_ELSE:
		// сюда можно попасть только если if ветка не была пропущена
		// так как если if ветка пропускается, то else директива обрабатывается сразу
		localIfNumber = 1;
		while ((c != EOF) && (localIfNumber > 0))
		{
			c = fgetc(f);
			while (c != '#')
				c = fgetc(f);
			// # was found
			GetDirective(f);
			if ((buf == "ifdef") || (buf == "ifndef")) //attention !
			{
				++ifNumber;
				++localIfNumber;
			}
			else if (buf == "endif") //attention !
			{
				--ifNumber;
				--localIfNumber;
			}
			else
				throw PPException();
		}
		break;
		
	}
	return c;
}

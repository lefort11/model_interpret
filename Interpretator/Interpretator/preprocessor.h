#pragma once

#include "String.h"
#include "Lexeme.h"
#include <list>
#include <iostream>


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
	enum PPState
	{
		//PP_START,
		PP_KEYWORD,
		PP_NAME,
		PP_HANDLER
	};

	static const PPLexemeType PPLexemes[];
	static const char* PPWords[];


	list<String> defined;

	static int ifNumber;

	int c;
	String buf;
	PPState state;
	
public:
	static int GetIfNumber()
	{
		return ifNumber;
	}

	static PPLexemeType IsPPWord(const char* word);

	Preprocessor() : c(0), buf(10, 0), state(PP_KEYWORD) {}

	void Handler(FILE* f, IdentTable& identTable, int& lastIdent); //return int here?

	void GetDirective(FILE* f);

	String ReadIdent(FILE* f);
	
	int ReadNumb(FILE* f);

	list<String>::iterator IsDefined(String name);

};


inline list<String>::iterator Preprocessor::IsDefined(String name)
{
	list<String>::iterator it = defined.begin();
	while( (it != defined.end()) )
	{
		if ((*it) == name)
			return it;
		++it;
	}
	return it;
}

int ifNumber = 0;

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
	"ifndef"
	"else",
	"endif",
	nullptr
};



inline PPLexemeType Preprocessor::IsPPWord(const char* word)
{
	int i = 1;
	while(PPWords[i] != nullptr)
	{
		if (strcmp(word, PPWords[i]))
			return PPLexemes[i];
		++i;
	}
	return PP_VOID;
}



inline void Preprocessor::GetDirective(FILE* f) 
{
	c = fgetc(f);
	while((c != ' ') || (c != '\n') || (c != '\r'))
	{
		buf += c;
		c = fgetc(f);
	}
}

inline String Preprocessor::ReadIdent(FILE* f)
{
	while (c == ' ')
		c = fgetc(f);
	String buf(10, 0);
	while((c != ' ') && (c != '\n') && (c != '\r') && (isalpha(c)) && (c != EOF))
	{
		buf += c;
		c = fgetc(f);
	}
	//now digits are coming
	if (buf == String(""))
		throw "a";
	while(isdigit(c))
	{
		buf += c;
		c = fgetc(f);
	}
	return buf;
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
	if (buf == String(""))
		throw "a";
	return atoi(buf);
}





inline void Preprocessor::Handler(FILE* f, IdentTable& identTable, int& lastIdent)
{
	// firstly a directive should be read
	buf.Clear();
	GetDirective(f);
	int position;
	String idName;
	PPLexemeType type = IsPPWord(buf);
	list<String>::iterator it;
	int localIfNumber;
	switch(type)
	{
	case PP_VOID:
		throw "a";

	case PP_DEFINE:
		//now identifier should be read
		state = PP_NAME;
		//#define asd 213
		if (c != ' ')
			throw "a";
		idName = ReadIdent(f);
		position = identTable.Search(buf);
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
		defined.push_back(idName);
		break;

	case PP_UNDEF:
		if (c != ' ')
			throw "a";
		idName = ReadIdent(f);
		it = IsDefined(idName);
		/*it = defined.begin();
		while(it != defined.end())
		{
			if( (*it) == idName )
			{
				defined.erase(it);
				position = identTable.Search(idName);
				identTable[position].ChangeName(nullptr);
				break;
			}
			++it;
		} */
		if (it == defined.end()) // not found => error
			throw "a";
		defined.erase(it); //deleting from defined list
		position = identTable.Search(idName);
		identTable[position].ChangeName(nullptr); //renaming of named constant to make defining again possible
		break;

	case PP_IFDEF:
		localIfNumber = 1;
		++ifNumber;
		idName = ReadIdent(f); // c = ' ' or '\n' after that
		if(IsDefined(idName) == defined.end())
		{
			while ((c != EOF) && (localIfNumber > 0))
			{
				c = fgetc(f);
				while (c != '#')
					c = fgetc(f);
				// # was found
				buf.Clear();
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
					throw "a";

			}
		}
		break;


	case PP_IFNDEF:
		localIfNumber = 1;
		++ifNumber;
		idName = ReadIdent(f); // c = ' ' or '\n' after that
		if (IsDefined(idName) != defined.end())
		{
			while ((c != EOF) && (localIfNumber > 0))
			{
				c = fgetc(f);
				while (c != '#')
					c = fgetc(f);
				// # was found
				buf.Clear();
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
					throw "a";

			}
		}
		break;
		

	case PP_ENDIF:
		--ifNumber;
		if (ifNumber < 0)
			throw "a";
		break;

	case PP_ELSE:
		localIfNumber = 1;
		while ((c != EOF) && (localIfNumber > 0))
		{
			c = fgetc(f);
			while (c != '#')
				c = fgetc(f);
			// # was found
			buf.Clear();
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
			else
				throw "a";
		}
		break;
		
	}
}

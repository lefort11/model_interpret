#include "preprocessor.h"

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

int Preprocessor::ifNumber = 0;


int Preprocessor::Handler(FILE* f, IdentTable& identTable, int& lastIdent)
{
	// firstly a directive should be read
	GetDirective(f);
	int position;
	PPLexemeType type = IsPPWord(buf);
	list<String>::iterator it;
	int localIfNumber;
	switch (type)
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
		if (position == -1)
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
					  //if no ident was read then it throws an exception
		if (IsDefined(buf) == defined.end())
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
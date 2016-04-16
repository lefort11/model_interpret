#include "testing.h"
#include "../Lexeme.h"

TEST(lexTablePush)
		{
			Lexeme lex1(LEXEME_PROGRAM, 0);
			Lexeme lex2(LEXEME_AND, 0);
			Lexeme lex3(LEXEME_ELSE, 0);
			LexemeTable lTable(lex1);
			lTable.Push(lex2);
			lTable.Push(lex3);
			assert((lTable[0] == lex1) && (lTable[1] == lex2) && (lTable[2] == lex3));

		};

TEST(identTableSearch)
		{
			String string1("Oleg hui");
			Identifier id(STRING_CONST, string1, 0,0, nullptr);
			IdentTable idTable(id);
			assert(idTable.Search(string1) == 0);
		};

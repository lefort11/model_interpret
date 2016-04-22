#include "../Scanner.h"
#include "testing.h"

/*TEST(GetLexemeTest)
		{
			Scanner scanner("/Users/Gleb/Desktop/model_interpret/Interpretator/Interpretator/tests/test.txt");
			scanner.GetChar();
			Lexeme lex = scanner.GetLexeme();
			assert(lex == LEXEME_PROGRAM);

		}; */

TEST(MakeLexemeTableTest)
		{
			Scanner scanner("/Users/Gleb/Desktop/model_interpret/Interpretator/Interpretator/tests/test.txt");
			scanner.MakeLexemeTable();
			assert(Scanner::lexemeTable[0] == LEXEME_PROGRAM);
			assert(Scanner::lexemeTable[1] == LEXEME_LPARENTH);
			assert(Scanner::lexemeTable[2] == LEXEME_INT);
			assert(Scanner::lexemeTable[3] == Lexeme(LEXEME_NAME, 0)); //a
			assert(Scanner::lexemeTable[4] == LEXEME_ASSIGNMENT);
			assert(Scanner::lexemeTable[5] == Lexeme(LEXEME_INT_CONST, 1)); //51
			assert(Scanner::lexemeTable[6] == LEXEME_COMMA);
			assert(Scanner::lexemeTable[7] == Lexeme(LEXEME_NAME, 2)); //b
			assert(Scanner::lexemeTable[8] == LEXEME_ASSIGNMENT);
			assert(Scanner::lexemeTable[9] == Lexeme(LEXEME_INT_CONST, 3)); //6
			assert(Scanner::lexemeTable[10] == LEXEME_COMMA);
			assert(Scanner::lexemeTable[11] == Lexeme(LEXEME_NAME, 4)); //c
			assert(Scanner::lexemeTable[12] == LEXEME_SEMICOLON);
			assert(Scanner::lexemeTable[13] == LEXEME_STRING);
			assert(Scanner::lexemeTable[14] == Lexeme(LEXEME_NAME, 5)); //x
			assert(Scanner::lexemeTable[15] == LEXEME_ASSIGNMENT);
			assert(Scanner::lexemeTable[16] == Lexeme(LEXEME_STRING_CONST, 6)); //abc
			assert(Scanner::lexemeTable[17] == LEXEME_COMMA);
			assert(Scanner::lexemeTable[18] == Lexeme(LEXEME_NAME, 7)); //y
			assert(Scanner::lexemeTable[19] == LEXEME_COMMA);
			assert(Scanner::lexemeTable[20] == Lexeme(LEXEME_NAME, 8)); //z
			assert(Scanner::lexemeTable[21] == LEXEME_ASSIGNMENT);
			assert(Scanner::lexemeTable[22] == Lexeme(LEXEME_STRING_CONST, 9)); //abcd
			assert(Scanner::lexemeTable[23] == LEXEME_SEMICOLON);
			assert(Scanner::lexemeTable[24] == Lexeme(LEXEME_NAME, 4));
			assert(Scanner::lexemeTable[25] == LEXEME_ASSIGNMENT);
			assert(Scanner::lexemeTable[26] == LEXEME_LBRACKET);
			assert(Scanner::lexemeTable[27] == Lexeme(LEXEME_NAME, 0));
			assert(Scanner::lexemeTable[28] == LEXEME_PLUS);
			assert(Scanner::lexemeTable[29] == Lexeme(LEXEME_NAME, 2));
			assert(Scanner::lexemeTable[30] == LEXEME_RBRACKET);
			assert(Scanner::lexemeTable[31] == LEXEME_MULTIPLE);
			assert(Scanner::lexemeTable[32] == Lexeme(LEXEME_REAL_CONST, 10)); //2.1
			assert(Scanner::lexemeTable[33] == LEXEME_SEMICOLON);
			assert(Scanner::lexemeTable[34] == LEXEME_IF);
			assert(Scanner::lexemeTable[35] == LEXEME_LBRACKET);
			assert(Scanner::lexemeTable[36] == Lexeme(LEXEME_NAME, 4));
			assert(Scanner::lexemeTable[37] == LEXEME_MORE_OR_EQUAL);
			assert(Scanner::lexemeTable[38] == Lexeme(LEXEME_INT_CONST, 11)); //100
			assert(Scanner::lexemeTable[39] == LEXEME_OR);
			assert(Scanner::lexemeTable[40] == Lexeme(LEXEME_NAME, 5));
			assert(Scanner::lexemeTable[41] == LEXEME_EQUAL);
			assert(Scanner::lexemeTable[42] == Lexeme(LEXEME_NAME, 8));
			assert(Scanner::lexemeTable[43] == LEXEME_RBRACKET);
			assert(Scanner::lexemeTable[44] == LEXEME_LPARENTH);

			assert(Scanner::lexemeTable[45] == LEXEME_READ);
			//cout << Scanner::lexemeTable[46].GetType() << endl;
			assert(Scanner::lexemeTable[46] == LEXEME_LBRACKET);
			assert(Scanner::lexemeTable[47] == Lexeme(LEXEME_NAME, 7));
			//cout << Scanner::lexemeTable[47].GetType() << endl;
			//cout << Scanner::lexemeTable[47].GetValue() << endl;
			assert(Scanner::lexemeTable[48] == LEXEME_RBRACKET);

		};

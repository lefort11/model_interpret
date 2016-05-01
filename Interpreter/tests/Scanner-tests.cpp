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
			Scanner scanner("/Users/Gleb/Desktop/model_interpret/Interpreter/tests/test.txt");
			scanner.MakeLexemeTable();
			assert(scanner.lexemeTable[0] == LEXEME_PROGRAM);
			assert(scanner.lexemeTable[1] == LEXEME_LPARENTH);
			assert(scanner.lexemeTable[2] == LEXEME_INT);
			assert(scanner.lexemeTable[3] == Lexeme(LEXEME_NAME, 0)); //a
			assert(scanner.lexemeTable[4] == LEXEME_ASSIGNMENT);
			assert(scanner.lexemeTable[5] == Lexeme(LEXEME_INT_CONST, 1)); //51
			assert(scanner.lexemeTable[6] == LEXEME_COMMA);
			assert(scanner.lexemeTable[7] == Lexeme(LEXEME_NAME, 2)); //b
			assert(scanner.lexemeTable[8] == LEXEME_ASSIGNMENT);
			assert(scanner.lexemeTable[9] == Lexeme(LEXEME_INT_CONST, 3)); //6
			assert(scanner.lexemeTable[10] == LEXEME_COMMA);
			assert(scanner.lexemeTable[11] == Lexeme(LEXEME_NAME, 4)); //c
			assert(scanner.lexemeTable[12] == LEXEME_SEMICOLON);
			assert(scanner.lexemeTable[13] == LEXEME_STRING);
			assert(scanner.lexemeTable[14] == Lexeme(LEXEME_NAME, 5)); //x
			assert(scanner.lexemeTable[15] == LEXEME_ASSIGNMENT);
			assert(scanner.lexemeTable[16] == Lexeme(LEXEME_STRING_CONST, 6)); //abc
			assert(scanner.lexemeTable[17] == LEXEME_COMMA);
			assert(scanner.lexemeTable[18] == Lexeme(LEXEME_NAME, 7)); //y
			assert(scanner.lexemeTable[19] == LEXEME_COMMA);
			assert(scanner.lexemeTable[20] == Lexeme(LEXEME_NAME, 8)); //z
			assert(scanner.lexemeTable[21] == LEXEME_ASSIGNMENT);
			assert(scanner.lexemeTable[22] == Lexeme(LEXEME_STRING_CONST, 9)); //abcd
			assert(scanner.lexemeTable[23] == LEXEME_SEMICOLON);
			assert(scanner.lexemeTable[24] == Lexeme(LEXEME_NAME, 4));
			assert(scanner.lexemeTable[25] == LEXEME_ASSIGNMENT);
			assert(scanner.lexemeTable[26] == LEXEME_LBRACKET);
			assert(scanner.lexemeTable[27] == Lexeme(LEXEME_NAME, 0));
			assert(scanner.lexemeTable[28] == LEXEME_PLUS);
			assert(scanner.lexemeTable[29] == Lexeme(LEXEME_NAME, 2));
			assert(scanner.lexemeTable[30] == LEXEME_RBRACKET);
			assert(scanner.lexemeTable[31] == LEXEME_MULTIPLY);
			assert(scanner.lexemeTable[32] == Lexeme(LEXEME_REAL_CONST, 10)); //2.1
			assert(scanner.lexemeTable[33] == LEXEME_SEMICOLON);
			assert(scanner.lexemeTable[34] == LEXEME_IF);
			assert(scanner.lexemeTable[35] == LEXEME_LBRACKET);
			assert(scanner.lexemeTable[36] == Lexeme(LEXEME_NAME, 4));
			assert(scanner.lexemeTable[37] == LEXEME_MORE_OR_EQUAL);
			assert(scanner.lexemeTable[38] == Lexeme(LEXEME_INT_CONST, 11)); //100
			assert(scanner.lexemeTable[39] == LEXEME_OR);
			assert(scanner.lexemeTable[40] == Lexeme(LEXEME_NAME, 5));
			assert(scanner.lexemeTable[41] == LEXEME_EQUAL);
			assert(scanner.lexemeTable[42] == Lexeme(LEXEME_NAME, 8));
			assert(scanner.lexemeTable[43] == LEXEME_RBRACKET);
			assert(scanner.lexemeTable[44] == LEXEME_LPARENTH);

			assert(scanner.lexemeTable[45] == LEXEME_READ);
			assert(scanner.lexemeTable[46] == LEXEME_LBRACKET);
			assert(scanner.lexemeTable[47] == Lexeme(LEXEME_NAME, 7));
			assert(scanner.lexemeTable[48] == LEXEME_RBRACKET);
			assert(scanner.lexemeTable[49] == LEXEME_SEMICOLON);
			assert(scanner.lexemeTable[50] == LEXEME_WRITE);
			assert(scanner.lexemeTable[51] == LEXEME_LBRACKET);
			assert(scanner.lexemeTable[52] == Lexeme(LEXEME_NAME, 7));
			assert(scanner.lexemeTable[53] == LEXEME_RBRACKET);
			assert(scanner.lexemeTable[54] == LEXEME_SEMICOLON);

			assert(scanner.lexemeTable[55] == LEXEME_WRITE);
			assert(scanner.lexemeTable[56] == LEXEME_LBRACKET);
			assert(scanner.lexemeTable[57] == Lexeme(LEXEME_NAME, 5));
			assert(scanner.lexemeTable[58] == LEXEME_PLUS);
			assert(scanner.lexemeTable[59] == Lexeme(LEXEME_NAME, 7));
			assert(scanner.lexemeTable[60] == LEXEME_PLUS);
			assert(scanner.lexemeTable[61] == Lexeme(LEXEME_NAME, 8));
			assert(scanner.lexemeTable[62] == LEXEME_COMMA);
			assert(scanner.lexemeTable[63] == Lexeme(LEXEME_NAME, 4));
			assert(scanner.lexemeTable[64] == LEXEME_RBRACKET);
			assert(scanner.lexemeTable[65] == LEXEME_SEMICOLON);

			assert(scanner.lexemeTable[66] == LEXEME_RPARENTH);
			assert(scanner.lexemeTable[67] == LEXEME_ELSE);

			assert(scanner.lexemeTable[68] == Lexeme(LEXEME_NAME, 4));
			assert(scanner.lexemeTable[69] == LEXEME_ASSIGNMENT);
			assert(scanner.lexemeTable[70] == Lexeme(LEXEME_NAME, 0));
			assert(scanner.lexemeTable[71] == LEXEME_ASSIGNMENT);
			assert(scanner.lexemeTable[72] == Lexeme(LEXEME_INT_CONST, 12)); //21
			assert(scanner.lexemeTable[73] == LEXEME_SEMICOLON);

			assert(scanner.lexemeTable[74] == LEXEME_WHILE);
			assert(scanner.lexemeTable[75] == LEXEME_LBRACKET);
			assert(scanner.lexemeTable[76] == Lexeme(LEXEME_NAME, 4));
			assert(scanner.lexemeTable[77] == LEXEME_MORE);
			assert(scanner.lexemeTable[78] == Lexeme(LEXEME_INT_CONST, 13)); // 100
			assert(scanner.lexemeTable[79] == LEXEME_RBRACKET);
			assert(scanner.lexemeTable[80] == LEXEME_LPARENTH);
			assert(scanner.lexemeTable[81] == Lexeme(LEXEME_NAME, 4));
			assert(scanner.lexemeTable[82] == LEXEME_ASSIGNMENT);
			assert(scanner.lexemeTable[83] == Lexeme(LEXEME_NAME, 4));
			assert(scanner.lexemeTable[84] == LEXEME_DIVISION);
			assert(scanner.lexemeTable[85] == Lexeme(LEXEME_INT_CONST, 14)); //5
			assert(scanner.lexemeTable[86] == LEXEME_SEMICOLON);

			assert(scanner.lexemeTable[87] == LEXEME_WRITE);
			assert(scanner.lexemeTable[88] == LEXEME_LBRACKET);
			assert(scanner.lexemeTable[89] == Lexeme(LEXEME_NAME, 4));
			assert(scanner.lexemeTable[90] == LEXEME_RBRACKET);
			assert(scanner.lexemeTable[91] == LEXEME_SEMICOLON);
			assert(scanner.lexemeTable[92] == Lexeme(LEXEME_NAME, 5));
			assert(scanner.lexemeTable[93] == LEXEME_ASSIGNMENT);
			assert(scanner.lexemeTable[94] == Lexeme(LEXEME_NAME, 5));
			assert(scanner.lexemeTable[95] == LEXEME_PLUS);
			assert(scanner.lexemeTable[96] == Lexeme(LEXEME_STRING_CONST, 15)); //"step"
			assert(scanner.lexemeTable[97] == LEXEME_SEMICOLON);
			assert(scanner.lexemeTable[98] == LEXEME_RPARENTH);
			assert(scanner.lexemeTable[99] == LEXEME_WRITE);
			assert(scanner.lexemeTable[100] == LEXEME_LBRACKET);
			assert(scanner.lexemeTable[101] == Lexeme(LEXEME_NAME, 5));
			assert(scanner.lexemeTable[102] == LEXEME_RBRACKET);
			assert(scanner.lexemeTable[103] == LEXEME_SEMICOLON);
			assert(scanner.lexemeTable[104] == LEXEME_RPARENTH);
			assert(scanner.lexemeTable[105] == LEXEME_END);

		};


#include "../Scanner.h"
#include "testing.h"

/*TEST(PPTest)
		{
			Scanner scanner("/Users/Gleb/Desktop/model_interpret/Interpretator/Interpretator/tests/test1.txt");
			scanner.MakeLexemeTable();
			assert(Scanner::lexemeTable[0] == LEXEME_PROGRAM);
			assert(Scanner::lexemeTable[1] == LEXEME_LPARENTH);
			assert(Scanner::lexemeTable[2] == LEXEME_INT);
			assert(Scanner::lexemeTable[3] == Lexeme(LEXEME_NAME, 1)); //a
			assert(Scanner::lexemeTable[4] == LEXEME_ASSIGNMENT);
			assert(Scanner::lexemeTable[5] == Lexeme(LEXEME_INT_CONST, 2)); //51
			assert(Scanner::lexemeTable[6] == LEXEME_COMMA);
			assert(Scanner::lexemeTable[7] == Lexeme(LEXEME_NAME, 3)); //b
			assert(Scanner::lexemeTable[8] == LEXEME_ASSIGNMENT);
			assert(Scanner::lexemeTable[9] == Lexeme(LEXEME_INT_CONST, 0)); //6
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
			assert(Scanner::lexemeTable[27] == Lexeme(LEXEME_NAME, 1));
			assert(Scanner::lexemeTable[28] == LEXEME_PLUS);
			assert(Scanner::lexemeTable[29] == Lexeme(LEXEME_NAME, 3));
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
			assert(Scanner::lexemeTable[46] == LEXEME_LBRACKET);
			assert(Scanner::lexemeTable[47] == Lexeme(LEXEME_NAME, 7));
			assert(Scanner::lexemeTable[48] == LEXEME_RBRACKET);
			assert(Scanner::lexemeTable[49] == LEXEME_SEMICOLON);
			assert(Scanner::lexemeTable[50] == LEXEME_WRITE);
			assert(Scanner::lexemeTable[51] == LEXEME_LBRACKET);
			assert(Scanner::lexemeTable[52] == Lexeme(LEXEME_NAME, 7));
			assert(Scanner::lexemeTable[53] == LEXEME_RBRACKET);
			assert(Scanner::lexemeTable[54] == LEXEME_SEMICOLON);

			assert(Scanner::lexemeTable[55] == LEXEME_WRITE);
			assert(Scanner::lexemeTable[56] == LEXEME_LBRACKET);
			assert(Scanner::lexemeTable[57] == Lexeme(LEXEME_NAME, 5));
			assert(Scanner::lexemeTable[58] == LEXEME_PLUS);
			assert(Scanner::lexemeTable[59] == Lexeme(LEXEME_NAME, 7));
			assert(Scanner::lexemeTable[60] == LEXEME_PLUS);
			assert(Scanner::lexemeTable[61] == Lexeme(LEXEME_NAME, 8));
			assert(Scanner::lexemeTable[62] == LEXEME_COMMA);
			assert(Scanner::lexemeTable[63] == Lexeme(LEXEME_NAME, 4));
			assert(Scanner::lexemeTable[64] == LEXEME_RBRACKET);
			assert(Scanner::lexemeTable[65] == LEXEME_SEMICOLON);

			assert(Scanner::lexemeTable[66] == LEXEME_RPARENTH);
			assert(Scanner::lexemeTable[67] == LEXEME_ELSE);

			assert(Scanner::lexemeTable[68] == Lexeme(LEXEME_NAME, 4));
			assert(Scanner::lexemeTable[69] == LEXEME_ASSIGNMENT);
			assert(Scanner::lexemeTable[70] == Lexeme(LEXEME_NAME, 1));
			assert(Scanner::lexemeTable[71] == LEXEME_ASSIGNMENT);
			assert(Scanner::lexemeTable[72] == Lexeme(LEXEME_INT_CONST, 12)); //21
			assert(Scanner::lexemeTable[73] == LEXEME_SEMICOLON);
#ifdef KEK
			assert(Scanner::lexemeTable[74] == LEXEME_WHILE);
			assert(Scanner::lexemeTable[75] == LEXEME_LBRACKET);
			assert(Scanner::lexemeTable[76] == Lexeme(LEXEME_NAME, 4));
			assert(Scanner::lexemeTable[77] == LEXEME_MORE);
			assert(Scanner::lexemeTable[78] == Lexeme(LEXEME_INT_CONST, 13)); // 100
			assert(Scanner::lexemeTable[79] == LEXEME_RBRACKET);
			assert(Scanner::lexemeTable[80] == LEXEME_LPARENTH);
			assert(Scanner::lexemeTable[81] == Lexeme(LEXEME_NAME, 4));
			assert(Scanner::lexemeTable[82] == LEXEME_ASSIGNMENT);
			assert(Scanner::lexemeTable[83] == Lexeme(LEXEME_NAME, 4));
			assert(Scanner::lexemeTable[84] == LEXEME_DIVISION);
			assert(Scanner::lexemeTable[85] == Lexeme(LEXEME_INT_CONST, 14)); //5
			assert(Scanner::lexemeTable[86] == LEXEME_SEMICOLON);

			assert(Scanner::lexemeTable[87] == LEXEME_WRITE);
			assert(Scanner::lexemeTable[88] == LEXEME_LBRACKET);
			assert(Scanner::lexemeTable[89] == Lexeme(LEXEME_NAME, 4));
			assert(Scanner::lexemeTable[90] == LEXEME_RBRACKET);
			assert(Scanner::lexemeTable[91] == LEXEME_SEMICOLON);
			assert(Scanner::lexemeTable[92] == Lexeme(LEXEME_NAME, 5));
			assert(Scanner::lexemeTable[93] == LEXEME_ASSIGNMENT);
			assert(Scanner::lexemeTable[94] == Lexeme(LEXEME_NAME, 5));
			assert(Scanner::lexemeTable[95] == LEXEME_PLUS);
			assert(Scanner::lexemeTable[96] == Lexeme(LEXEME_STRING_CONST, 15)); //"step"
			assert(Scanner::lexemeTable[97] == LEXEME_SEMICOLON);
			assert(Scanner::lexemeTable[98] == LEXEME_RPARENTH);
			assert(Scanner::lexemeTable[99] == LEXEME_WRITE);
			assert(Scanner::lexemeTable[100] == LEXEME_LBRACKET);
			assert(Scanner::lexemeTable[101] == Lexeme(LEXEME_NAME, 5));
			assert(Scanner::lexemeTable[102] == LEXEME_RBRACKET);
			assert(Scanner::lexemeTable[103] == LEXEME_SEMICOLON);
#endif

			assert(Scanner::lexemeTable[74] == LEXEME_RPARENTH);
			assert(Scanner::lexemeTable[75] == LEXEME_END);
			};
*/


TEST(PPtest2)
		{
			Scanner scanner("/Users/Gleb/Desktop/model_interpret/Interpretator/Interpretator/tests/test2.txt");
			scanner.MakeLexemeTable();
			assert(Scanner::lexemeTable[0] == LEXEME_PROGRAM);
			assert(Scanner::lexemeTable[1] == LEXEME_LPARENTH);
			assert(Scanner::lexemeTable[2] == LEXEME_INT);
			assert(Scanner::lexemeTable[3] == Lexeme(LEXEME_NAME, 1)); //a
			assert(Scanner::lexemeTable[4] == LEXEME_ASSIGNMENT);
			assert(Scanner::lexemeTable[5] == Lexeme(LEXEME_INT_CONST, 2)); //51
			assert(Scanner::lexemeTable[6] == LEXEME_COMMA);
			assert(Scanner::lexemeTable[7] == Lexeme(LEXEME_NAME, 3)); //b
			assert(Scanner::lexemeTable[8] == LEXEME_ASSIGNMENT);
			assert(Scanner::lexemeTable[9] == Lexeme(LEXEME_INT_CONST, 0)); //6
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
			assert(Scanner::lexemeTable[24] == LEXEME_LPARENTH);
			assert(Scanner::lexemeTable[25] == LEXEME_READ);
			assert(Scanner::lexemeTable[26] == LEXEME_LBRACKET);
			assert(Scanner::lexemeTable[27] == Lexeme(LEXEME_NAME, 7));
			assert(Scanner::lexemeTable[28] == LEXEME_RBRACKET);
			assert(Scanner::lexemeTable[29] == LEXEME_SEMICOLON);
			assert(Scanner::lexemeTable[30] == LEXEME_WRITE);
			assert(Scanner::lexemeTable[31] == LEXEME_LBRACKET);
			assert(Scanner::lexemeTable[32] == Lexeme(LEXEME_NAME, 5));
			assert(Scanner::lexemeTable[33] == LEXEME_PLUS);
			assert(Scanner::lexemeTable[34] == Lexeme(LEXEME_NAME, 7));
			assert(Scanner::lexemeTable[35] == LEXEME_PLUS);
			assert(Scanner::lexemeTable[36] == Lexeme(LEXEME_NAME, 8));
			assert(Scanner::lexemeTable[37] == LEXEME_COMMA);
			assert(Scanner::lexemeTable[38] == Lexeme(LEXEME_NAME, 4));
			assert(Scanner::lexemeTable[39] == LEXEME_RBRACKET);
			assert(Scanner::lexemeTable[40] == LEXEME_SEMICOLON);
			assert(Scanner::lexemeTable[41] == LEXEME_RPARENTH);
			assert(Scanner::lexemeTable[42] == LEXEME_ELSE);
			assert(Scanner::lexemeTable[43] == Lexeme(LEXEME_NAME, 4));
			assert(Scanner::lexemeTable[44] == LEXEME_ASSIGNMENT);
			assert(Scanner::lexemeTable[45] == Lexeme(LEXEME_NAME, 1));
			assert(Scanner::lexemeTable[46] == LEXEME_ASSIGNMENT);
			assert(Scanner::lexemeTable[47] == Lexeme(LEXEME_INT_CONST, 10)); //21
			assert(Scanner::lexemeTable[48] == LEXEME_SEMICOLON);
			assert(Scanner::lexemeTable[49] == LEXEME_WRITE);
			assert(Scanner::lexemeTable[50] == LEXEME_LBRACKET);
			assert(Scanner::lexemeTable[51] == Lexeme(LEXEME_NAME, 5));
			assert(Scanner::lexemeTable[52] == LEXEME_RBRACKET);
			assert(Scanner::lexemeTable[53] == LEXEME_SEMICOLON);
			assert(Scanner::lexemeTable[54] == LEXEME_RPARENTH);
			assert(Scanner::lexemeTable[55] == LEXEME_END);
		};

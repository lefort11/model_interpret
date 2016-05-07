#include "testing.h"
#include "../Parser/Parser.h"

TEST(RPMTests)
		{
			Parser parser("/Users/Gleb/Desktop/model_interpret/Interpreter/tests/test3.txt");
			parser.Analyze();
			assert(parser.program[0].GetType() == RPM_ADDRESS);
			assert(parser.program[0].GetValue() == 4);
			assert(parser.program[1].GetType() == LEXEME_NAME);
			assert(parser.program[2].GetType() == LEXEME_NAME);
			assert(parser.program[3].GetType() == LEXEME_PLUS);
			assert(parser.program[4].GetType() == LEXEME_REAL_CONST);
			assert(parser.program[5].GetType() == LEXEME_MULTIPLY);
			assert(parser.program[6].GetType() == LEXEME_ASSIGNMENT);
			assert(parser.program[7].GetType() == RPM_OUT_OF_STACK);
			assert(parser.program[8].GetType() == LEXEME_NAME);
			assert(parser.program[9].GetType() == LEXEME_INT_CONST);
			assert(parser.program[10].GetType() == LEXEME_MORE_OR_EQUAL);
			assert(parser.program[11].GetType() == LEXEME_NAME);
			assert(parser.program[12].GetType() == LEXEME_NAME);
			assert(parser.program[13].GetType() == LEXEME_EQUAL);
			assert(parser.program[14].GetType() == LEXEME_OR);
			assert(parser.program[15].GetType() == RPM_LABEL);
			assert(parser.program[16].GetType() == RPM_FALSE_GOTO);
			assert(parser.program[17].GetType() == RPM_ADDRESS);
			assert(parser.program[18].GetType() == LEXEME_READ);


		};
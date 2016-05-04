#pragma once

#include "../Parser/Parser.h"

class Executor
{
	Lexeme currentLexeme;

public:
	
	class ExecutorException {};

	void Execute(ReversePolishNotation &program);


};
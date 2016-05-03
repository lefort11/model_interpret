#pragma once

#include "Parser.h"

class Executor
{
	Lexeme currentLexeme;

public:
	
	class ExecutorException {};

	void execute(ReversePolishNotation& program);


};
#pragma once

#include "Parser.h"

class Executor
{
	Lexeme currentLexeme;

public:
	
	class ExecutorException {};

	void Execute(ReversePolishNotation &program);


};
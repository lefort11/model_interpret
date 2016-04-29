#include "Parser.h"


void Parser::Analyze()
{
	GetLexeme();
	if(currentLexeme == LEXEME_PROGRAM)
	{
		GetLexeme();
		Program();
		if (currentLexeme != LEXEME_END)
			throw ParserException();
	}
	else throw ParserException();
}


void Parser::Program()
{
	if (currentLexeme == LEXEME_LPARENTH)
	{
		GetLexeme();
		Descriptions();
		Operators();
		if (currentLexeme != LEXEME_RPARENTH)
			throw ParserException();
		GetLexeme();
	}
	else
		throw ParserException();
}

void Parser::Descriptions()
{
	while (currentLexeme == LEXEME_STRUCT)
	{
		//GetLexeme();
		StructDescription(); //currentLexeme == LEXEME_SEMICOLON ???
		//GetLexeme();
	}
	while ((currentLexeme == LEXEME_INT) || (currentLexeme == LEXEME_REAL) || (currentLexeme == LEXEME_STRING) || ((currentLexeme.GetType() == LEXEME_NAME) && (scanner.identTable[currentLexeme.GetValue()].GetType() == STRUCT_NAME)))
	{
		//GetLexeme();
		VariableDescription();
		//GetLexeme();
	}
}


void Parser::StructDescription()
{
	//currentLexeme == LEXEME_STRUCT
	GetLexeme();
	if (currentLexeme.GetType() == LEXEME_NAME)
	{
		scanner.identTable[currentLexeme.GetValue()].ChangeType(STRUCT_NAME);
		GetLexeme();
		if(currentLexeme == LEXEME_LPARENTH)
		{
			GetLexeme();
			if ((currentLexeme == LEXEME_INT) || (currentLexeme == LEXEME_REAL) || (currentLexeme == LEXEME_STRING))
			{
				VariableDescription(); //??
				GetLexeme();
			}
			else
				throw ParserException();
			while ((currentLexeme == LEXEME_INT) || (currentLexeme == LEXEME_REAL) || (currentLexeme == LEXEME_STRING))
			{
				VariableDescription(); // ??
				GetLexeme();
			}
			if(currentLexeme == LEXEME_RPARENTH)
			{
				GetLexeme();
				if (currentLexeme == LEXEME_SEMICOLON)
					GetLexeme();
				else
					throw ParserException();
			}
			else throw ParserException();
		}
	}
	else
		throw ParserException();
}


void Parser::VariableDescription()
{
	auto type = currentLexeme.GetType(); // saving current type of variable
	GetLexeme();
	if (currentLexeme.GetType() != LEXEME_NAME)
		throw ParserException();
	while ((currentLexeme.GetType() == LEXEME_NAME))
	{
		scanner.identTable[currentLexeme.GetValue()].Declare(); //making identifier declared
		switch (type)
		{
		case LEXEME_INT:
			scanner.identTable[currentLexeme.GetValue()].ChangeType(INT);
			break;
		case LEXEME_REAL:
			scanner.identTable[currentLexeme.GetValue()].ChangeType(REAL);
			break;
		case LEXEME_STRING:
			scanner.identTable[currentLexeme.GetValue()].ChangeType(STRING);
			break;
		case LEXEME_NAME:
			scanner.identTable[currentLexeme.GetValue()].ChangeType(USER);
			break;
		default:
			throw ParserException();
		} //defining type
		GetLexeme();
		
		if (currentLexeme == LEXEME_ASSIGNMENT)
		{
			GetLexeme();
			switch (type)
			{
			case LEXEME_INT:
				if (currentLexeme.GetType() != LEXEME_INT_CONST)
					throw ParserException();
				//since this constant follows the declared variable
				//this will be truth
				//... I hope
				scanner.identTable[currentLexeme.GetValue() - 1].ChangeIntValue(scanner.identTable[currentLexeme.GetValue()].GetIntValue());
				break;

			case LEXEME_REAL:
				if (currentLexeme.GetType() != LEXEME_REAL_CONST)
					throw ParserException();
				scanner.identTable[currentLexeme.GetValue() - 1].ChangeRealValue(scanner.identTable[currentLexeme.GetValue()].GetRealValue());
				break;

			case LEXEME_STRING:
				if (currentLexeme.GetType() != LEXEME_STRING_CONST)
					throw ParserException();
				scanner.identTable[currentLexeme.GetValue() - 1].ChangeStringValue(scanner.identTable[currentLexeme.GetValue()].GetStringValue());
				break;

			default:
				throw ParserException();
			}
			GetLexeme();
		}
		// comma or semicolon after that
		if (currentLexeme == LEXEME_COMMA)
		{
			GetLexeme();
			if (currentLexeme.GetType() != LEXEME_NAME) // if there is no name after comma -> error
				throw ParserException();
		}
	}

	if (currentLexeme != LEXEME_SEMICOLON)
		throw ParserException();
	GetLexeme();

}

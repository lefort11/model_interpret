#include "Parser.h"void Parser::Analyze(){	GetLexeme();	if(currentLexeme == LEXEME_PROGRAM)	{		GetLexeme();		Program();		if (currentLexeme != LEXEME_END)			throw ParserException();	}	else throw ParserException();}void Parser::Program(){	if (currentLexeme == LEXEME_LPARENTH)	{		GetLexeme();		Descriptions();		Operators();		if (currentLexeme != LEXEME_RPARENTH)			throw ParserException();		GetLexeme();	}	else		throw ParserException();}void Parser::Descriptions(){	while (currentLexeme == LEXEME_STRUCT)	{		StructDescription(); //currentLexeme == LEXEME_SEMICOLON ???	}	while ((currentLexeme == LEXEME_INT) || (currentLexeme == LEXEME_REAL) || (currentLexeme == LEXEME_STRING) || ((currentLexeme.GetType() == LEXEME_NAME) && (scanner.identTable[currentLexeme.GetValue()].GetType() == STRUCT_NAME)))	{		VariableDescription();	}}void Parser::StructDescription(){	/* � ������� ������ �������� �������-����� ��������� - ����� � ������� ���� ����		� ������� ���� ���� �������� ����� - ����� � ������� ��������, ������� ������������ ����� ������ ������ ���������������		������ ��� ����� ��������� �������� � ������������� ������� ���������������	*/	//currentLexeme == LEXEME_STRUCT	GetLexeme();	if (currentLexeme.GetType() == LEXEME_NAME)	{		scanner.identTable[currentLexeme.GetValue()].ChangeType(STRUCT_NAME);		scanner.identTable[currentLexeme.GetValue()].ChangeIntValue(lastStructureNumber);		structuresVector.push_back(IdentTable());		//std::vector<IdentTable>::iterator it = --structures.end(); // iterator pointing at the last structure		GetLexeme();		if(currentLexeme == LEXEME_LPARENTH)		{			GetLexeme();			if ((currentLexeme == LEXEME_INT) || (currentLexeme == LEXEME_REAL) || (currentLexeme == LEXEME_STRING))			{				StructureMemberDescription(); //??				GetLexeme();			}			else				throw ParserException();			while ((currentLexeme == LEXEME_INT) || (currentLexeme == LEXEME_REAL) || (currentLexeme == LEXEME_STRING))			{				StructureMemberDescription(); // ??				GetLexeme();			}			if(currentLexeme == LEXEME_RPARENTH)			{				GetLexeme();				if (currentLexeme == LEXEME_SEMICOLON)					GetLexeme();				else					throw ParserException();			}			else throw ParserException();		}		++lastStructureNumber;	}	else		throw ParserException();}void Parser::VariableDescription(){	auto lexemeType = currentLexeme.GetType(); // saving current type of variable	GetLexeme();	if (currentLexeme.GetType() != LEXEME_NAME)		throw ParserException();	while ((currentLexeme.GetType() == LEXEME_NAME))	{		auto value = currentLexeme.GetValue();		if (scanner.identTable[value].isDeclared())			throw ParserException();		scanner.identTable[value].Declare(); //making identifier declared		switch (lexemeType)		{			case LEXEME_INT:				scanner.identTable[value].ChangeType(INT);				break;			case LEXEME_REAL:				scanner.identTable[value].ChangeType(REAL);				break;			case LEXEME_STRING:				scanner.identTable[value].ChangeType(STRING);				break;			case LEXEME_NAME:				scanner.identTable[value].ChangeType(USER);				break;			default:				throw ParserException();		} //defining type		GetLexeme();				if (currentLexeme == LEXEME_ASSIGNMENT)		{			GetLexeme();			switch (lexemeType)			{				case LEXEME_INT:				{					bool unaryMinusFound = false;					if (currentLexeme == LEXEME_PLUS)						GetLexeme();					else if (currentLexeme == LEXEME_MINUS)					{						GetLexeme();						unaryMinusFound = true;					}					if (currentLexeme.GetType() != LEXEME_INT_CONST)						throw ParserException();					if(!unaryMinusFound)						scanner.identTable[value].ChangeIntValue(scanner.identTable[currentLexeme.GetValue()].GetIntValue());					else						scanner.identTable[value].ChangeIntValue(-scanner.identTable[currentLexeme.GetValue()].GetIntValue());					break;				}				case LEXEME_REAL:				{					bool unaryMinusFound = false;					if (currentLexeme == LEXEME_PLUS)						GetLexeme();					else if (currentLexeme == LEXEME_MINUS)					{						GetLexeme();						unaryMinusFound = true;					}					if (currentLexeme.GetType() != LEXEME_REAL_CONST)						throw ParserException();					if (!unaryMinusFound)						scanner.identTable[value].ChangeRealValue(scanner.identTable[currentLexeme.GetValue()].GetRealValue());					else						scanner.identTable[value].ChangeRealValue(-scanner.identTable[currentLexeme.GetValue()].GetRealValue());					break;				}				case LEXEME_STRING:				{					if (currentLexeme.GetType() != LEXEME_STRING_CONST)						throw ParserException();					scanner.identTable[value].ChangeStringValue(scanner.identTable[currentLexeme.GetValue()].GetStringValue());					break;				}				default:					throw ParserException();			}			GetLexeme();		}		// comma or semicolon after that		if (currentLexeme == LEXEME_COMMA)		{			GetLexeme();			if (currentLexeme.GetType() != LEXEME_NAME) // if there is no name after comma -> error				throw ParserException();		}	}	if (currentLexeme != LEXEME_SEMICOLON)		throw ParserException();	GetLexeme();}void Parser::Operators(){	while(currentLexeme != LEXEME_RPARENTH)	{		SingleOperator();	}}void Parser::SingleOperator(){	auto lexemeType = currentLexeme.GetType();	switch(lexemeType)	{		case LEXEME_INT:		{			GetLexeme();			if(currentLexeme.GetType() == LEXEME_LBRACKET)			{				GetLexeme();				Expression();				//currentLexeme == RBRACKET				if (currentLexeme.GetType() != LEXEME_RBRACKET)					throw ParserException();				GetLexeme();				SingleOperator();				// GetLexeme() ??				if (currentLexeme.GetType() != LEXEME_ELSE)					throw ParserException();				GetLexeme();				SingleOperator();				//GetLexeme(); ??			}			else throw ParserException();			break;		}		case LEXEME_WHILE:		{			GetLexeme();			if(currentLexeme.GetType() == LEXEME_LBRACKET)			{				GetLexeme();				Expression();				if (currentLexeme.GetType() != LEXEME_RBRACKET)					throw ParserException();				GetLexeme();				SingleOperator();			}			else throw ParserException();			break;		}		case LEXEME_BREAK:		{			// ???			break;		}		case LEXEME_GOTO:		{			GetLexeme();			if (currentLexeme.GetType() != LEXEME_NAME)				throw ParserException();			scanner.identTable[currentLexeme.GetValue()].ChangeType(LABEL);			GetLexeme();			if (currentLexeme.GetType() != LEXEME_SEMICOLON)				throw ParserException();			GetLexeme();			break;		}		case LEXEME_READ:		{			GetLexeme();			if (currentLexeme.GetType() != LEXEME_LBRACKET)				throw ParserException();			GetLexeme();			if (currentLexeme.GetType() != LEXEME_NAME)				throw ParserException();			if (!scanner.identTable[currentLexeme.GetValue()].isDeclared())				throw ParserException();			GetLexeme();			if (currentLexeme.GetType() != LEXEME_RBRACKET)				throw ParserException();			GetLexeme();			if (currentLexeme.GetType() != LEXEME_SEMICOLON)				throw ParserException();			GetLexeme();			break;		}		case LEXEME_WRITE:		{			GetLexeme();			if (currentLexeme.GetType() != LEXEME_LBRACKET)				throw ParserException();			GetLexeme();			Expression();			while (currentLexeme.GetType() == LEXEME_COMMA)			{				GetLexeme();				Expression();			}			if (currentLexeme.GetType() != LEXEME_RBRACKET)				throw ParserException();			GetLexeme();			if (currentLexeme.GetType() != LEXEME_SEMICOLON)				throw ParserException();			GetLexeme();			break;		}		case LEXEME_RPARENTH: // compound operator		{			GetLexeme();			Operators();			if (currentLexeme.GetType() != LEXEME_RPARENTH)				throw ParserException();			GetLexeme();			break;		}		case LEXEME_NAME:		{			//auto lexValue = currentLexeme.GetValue();			GetLexeme();			if (currentLexeme == LEXEME_COLON) // marked Operator			{				GetLexeme();				SingleOperator();			}			else //expression operator				Expression();			break;		}		case LEXEME_NOT: case LEXEME_MINUS: case LEXEME_INT_CONST: case LEXEME_STRING_CONST: case LEXEME_REAL_CONST:		{			Expression();		}		default:			throw ParserException();	}}void Parser::Expression(){	AssignmentExpression();	auto type = currentLexeme.GetType();	while (type == LEXEME_ASSIGNMENT)	{		GetLexeme();		AssignmentExpression();	}	}void Parser::AssignmentExpression(){	ArithmeticExpression();	auto type = currentLexeme.GetType();	while ((type == LEXEME_MORE) || (type == LEXEME_MORE_OR_EQUAL) || (type == LEXEME_LESS) || (type == LEXEME_LESS_OR_EQUAL) || (type == LEXEME_EQUAL) || (type == LEXEME_NOT_EQUAL))	{		GetLexeme();		ArithmeticExpression();	}}
void Parser::ArithmeticExpression(){	Summand();	while((currentLexeme.GetType() == LEXEME_PLUS) || (currentLexeme.GetType() == LEXEME_MINUS))	{		GetLexeme();		Summand();	}}void Parser::Summand(){	Factor();	while((currentLexeme.GetType() == LEXEME_MULTIPLY) || (currentLexeme.GetType() == LEXEME_DIVISION))	{		GetLexeme();		Factor();	}}void Parser::Factor(){	if ((currentLexeme.GetType() == LEXEME_MINUS) || (currentLexeme.GetType()))	{		GetLexeme();		Factor();	}	else if(currentLexeme.GetType() == LEXEME_LBRACKET)	{		GetLexeme();		Expression();		if (currentLexeme.GetType() != LEXEME_RBRACKET)			throw ParserException();		GetLexeme();	}	else if(currentLexeme.GetType() == LEXEME_NAME)	{		//add Poliz!!!		if(scanner.identTable[currentLexeme.GetValue()].GetType() == USER)		{			auto structNumb = scanner.identTable[currentLexeme.GetValue()].GetIntValue(); // the number in struct vector			GetLexeme();			if (currentLexeme.GetType() == LEXEME_POINT)			{				GetLexeme();				//checking if the name is the structure member;				if (currentLexeme.GetType() != LEXEME_NAME)					throw ParserException();				String name = scanner.identTable[currentLexeme.GetValue()].GetName();				if (structuresVector[structNumb].Search(name) == -1)					throw ParserException();			}			else				throw ParserException();		}		GetLexeme();	}}void Parser::StructureMemberDescription(){	auto type = currentLexeme.GetType();	int lastStructMemberNumber = 0;	GetLexeme();	if (currentLexeme != LEXEME_NAME)		throw ParserException();	while(currentLexeme == LEXEME_NAME)	{		structuresVector[lastStructureNumber].Push(scanner.identTable[currentLexeme.GetValue()]); // copying an identifier to the struct member table		switch(type)		{			case LEXEME_INT:			{				structuresVector[lastStructureNumber][lastStructMemberNumber].ChangeType(INT);				break;			}			case LEXEME_REAL:			{				structuresVector[lastStructureNumber][lastStructMemberNumber].ChangeType(REAL);				break;			}			case LEXEME_STRING:			{				structuresVector[lastStructureNumber][lastStructMemberNumber].ChangeType(STRING);				break;			}			default:				throw ParserException();		}		GetLexeme();		if (currentLexeme.GetType() == LEXEME_COMMA)			GetLexeme();		++lastStructMemberNumber;	}	if (currentLexeme.GetType() != LEXEME_SEMICOLON)		throw ParserException();}

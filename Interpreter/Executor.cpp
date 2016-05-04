#include "Executor.h"#include <deque>void Executor::Execute(ReversePolishNotation &program){		Stack<Identifier> argsStack(40);	int counter, end = program.GetFreeElementNumber();	for(counter = 0; counter < end; ++counter)	{		currentLexeme = program[counter];		switch(currentLexeme.GetType())		{						case LEXEME_NAME: case LEXEME_INT_CONST: case LEXEME_REAL_CONST: case LEXEME_STRING_CONST:			{				if(currentLexeme.GetType() == LEXEME_INT_CONST)					Parser::structuresVector[currentLexeme.GetTableNumber()][currentLexeme.GetValue()].ChangeType(INT);				else if(currentLexeme.GetType() == LEXEME_REAL_CONST)					Parser::structuresVector[currentLexeme.GetTableNumber()][currentLexeme.GetValue()].ChangeType(REAL);				else if(currentLexeme.GetType() == LEXEME_STRING_CONST)					Parser::structuresVector[currentLexeme.GetTableNumber()][currentLexeme.GetValue()].ChangeType(STRING);				/* это нужно для того, чтобы избежать лишних проверок, начиная с данного этапа CONST не нужен */				argsStack.Push(Parser::structuresVector[currentLexeme.GetTableNumber()][currentLexeme.GetValue()]);				break;			}			case LEXEME_PLUS:			{				auto secondOperand = argsStack.Pop(), firstOperand = argsStack.Pop();				if ((firstOperand.GetType() == INT) && (secondOperand.GetType() == INT))				{					firstOperand.ChangeIntValue(firstOperand.GetIntValue() + secondOperand.GetIntValue());					argsStack.Push(firstOperand);				}				else if ((firstOperand.GetType() == INT) && (secondOperand.GetType() == REAL))				{					secondOperand.ChangeRealValue(secondOperand.GetRealValue() + firstOperand.GetIntValue());					argsStack.Push(secondOperand);				}				else if ((firstOperand.GetType() == REAL) && (secondOperand.GetType() == INT))				{					firstOperand.ChangeRealValue(secondOperand.GetIntValue() + firstOperand.GetRealValue());					argsStack.Push(firstOperand);				}				else if ((firstOperand.GetType() == REAL) && (secondOperand.GetType() == REAL))				{					firstOperand.ChangeRealValue(firstOperand.GetRealValue() + secondOperand.GetRealValue());					argsStack.Push(firstOperand);				}				else if ((firstOperand.GetType() == STRING) && (secondOperand.GetType() == STRING))				{					firstOperand.ChangeStringValue(firstOperand.GetStringValue() + secondOperand.GetStringValue());					argsStack.Push(firstOperand);				}				else					throw ExecutorException();				break;			}			case LEXEME_MINUS:			{				auto secondOperand = argsStack.Pop(), firstOperand = argsStack.Pop();				if ((firstOperand.GetType() == INT) && (secondOperand.GetType() == INT))				{					firstOperand.ChangeIntValue(firstOperand.GetIntValue() - secondOperand.GetIntValue());					argsStack.Push(firstOperand);				}				else if ((firstOperand.GetType() == INT) && (secondOperand.GetType() == REAL))				{					secondOperand.ChangeRealValue(firstOperand.GetIntValue() - secondOperand.GetRealValue());					argsStack.Push(secondOperand);				}				else if ((firstOperand.GetType() == REAL) && (secondOperand.GetType() == INT))				{					firstOperand.ChangeRealValue(firstOperand.GetRealValue() - secondOperand.GetIntValue());					argsStack.Push(firstOperand);				}				else if ((firstOperand.GetType() == REAL) && (secondOperand.GetType() == REAL))				{					firstOperand.ChangeRealValue(firstOperand.GetRealValue() - secondOperand.GetRealValue());					argsStack.Push(firstOperand);				}				else					throw ExecutorException();				break;			}			case LEXEME_MULTIPLY:			{				auto secondOperand = argsStack.Pop(), firstOperand = argsStack.Pop();				if ((firstOperand.GetType() == INT) && (secondOperand.GetType() == INT))				{					firstOperand.ChangeIntValue(firstOperand.GetIntValue() * secondOperand.GetIntValue());					argsStack.Push(firstOperand);				}				else if ((firstOperand.GetType() == INT) && (secondOperand.GetType() == REAL))				{					secondOperand.ChangeRealValue(firstOperand.GetIntValue() * secondOperand.GetRealValue());					argsStack.Push(secondOperand);				}				else if ((firstOperand.GetType() == REAL) && (secondOperand.GetType() == INT))				{					firstOperand.ChangeRealValue(firstOperand.GetRealValue() * secondOperand.GetIntValue());					argsStack.Push(firstOperand);				}				else if ((firstOperand.GetType() == REAL) && (secondOperand.GetType() == REAL))				{					firstOperand.ChangeRealValue(firstOperand.GetRealValue() * secondOperand.GetRealValue());					argsStack.Push(firstOperand);				}				else					throw ExecutorException();				break;			}			case LEXEME_DIVISION:			{				auto secondOperand = argsStack.Pop(), firstOperand = argsStack.Pop();				if ((firstOperand.GetType() == INT) && (secondOperand.GetType() == INT))				{					firstOperand.ChangeIntValue(firstOperand.GetIntValue() / secondOperand.GetIntValue());					argsStack.Push(firstOperand);				}				else if ((firstOperand.GetType() == INT) && (secondOperand.GetType() == REAL))				{					secondOperand.ChangeRealValue(firstOperand.GetIntValue() / secondOperand.GetRealValue());					argsStack.Push(secondOperand);				}				else if ((firstOperand.GetType() == REAL) && (secondOperand.GetType() == INT))				{					firstOperand.ChangeRealValue(firstOperand.GetRealValue() / secondOperand.GetIntValue());					argsStack.Push(firstOperand);				}				else if ((firstOperand.GetType() == REAL) && (secondOperand.GetType() == REAL))				{					firstOperand.ChangeRealValue(firstOperand.GetRealValue() / secondOperand.GetRealValue());					argsStack.Push(firstOperand);				}				else					throw ExecutorException();				break;			}			case LEXEME_MORE:			{				auto secondOperand = argsStack.Pop(), firstOperand = argsStack.Pop();				Identifier id;				id.ChangeType(INT);				if ((firstOperand.GetType() == INT) && (secondOperand.GetType() == INT))				{					id.ChangeIntValue(firstOperand.GetIntValue() > secondOperand.GetIntValue());				}				else if ((firstOperand.GetType() == INT) && (secondOperand.GetType() == REAL))				{					id.ChangeIntValue(firstOperand.GetIntValue() > secondOperand.GetRealValue());				}				else if ((firstOperand.GetType() == REAL) && (secondOperand.GetType() == INT))				{					id.ChangeIntValue(firstOperand.GetRealValue() > secondOperand.GetIntValue());				}				else if ((firstOperand.GetType() == REAL) && (secondOperand.GetType() == REAL))				{					id.ChangeIntValue(firstOperand.GetRealValue() > secondOperand.GetRealValue());				}				else if((firstOperand.GetType() == STRING) && (secondOperand.GetType() == STRING))				{					id.ChangeIntValue(firstOperand.GetStringValue() > secondOperand.GetStringValue());				}				else					throw ExecutorException();				argsStack.Push(id);				break;			}			case LEXEME_MORE_OR_EQUAL:			{				auto secondOperand = argsStack.Pop(), firstOperand = argsStack.Pop();				Identifier id;				id.ChangeType(INT);				if ((firstOperand.GetType() == INT) && (secondOperand.GetType() == INT))				{					id.ChangeIntValue(firstOperand.GetIntValue() >= secondOperand.GetIntValue());				}				else if ((firstOperand.GetType() == INT) && (secondOperand.GetType() == REAL))				{					id.ChangeIntValue(firstOperand.GetIntValue() >= secondOperand.GetRealValue());				}				else if ((firstOperand.GetType() == REAL) && (secondOperand.GetType() == INT))				{					id.ChangeIntValue(firstOperand.GetRealValue() >= secondOperand.GetIntValue());				}				else if ((firstOperand.GetType() == REAL) && (secondOperand.GetType() == REAL))				{					id.ChangeIntValue(firstOperand.GetRealValue() >= secondOperand.GetRealValue());				}				else if ((firstOperand.GetType() == STRING) && (secondOperand.GetType() == STRING))				{					id.ChangeIntValue(firstOperand.GetStringValue() >= secondOperand.GetStringValue());				}				else					throw ExecutorException();				argsStack.Push(id);				break;			}			case LEXEME_LESS:			{				auto secondOperand = argsStack.Pop(), firstOperand = argsStack.Pop();				Identifier id;				id.ChangeType(INT);				if ((firstOperand.GetType() == INT) && (secondOperand.GetType() == INT))				{					id.ChangeIntValue(firstOperand.GetIntValue() < secondOperand.GetIntValue());				}				else if ((firstOperand.GetType() == INT) && (secondOperand.GetType() == REAL))				{					id.ChangeIntValue(firstOperand.GetIntValue() < secondOperand.GetRealValue());				}				else if ((firstOperand.GetType() == REAL) && (secondOperand.GetType() == INT))				{					id.ChangeIntValue(firstOperand.GetRealValue() < secondOperand.GetIntValue());				}				else if ((firstOperand.GetType() == REAL) && (secondOperand.GetType() == REAL))				{					id.ChangeIntValue(firstOperand.GetRealValue() < secondOperand.GetRealValue());				}				else if ((firstOperand.GetType() == STRING) && (secondOperand.GetType() == STRING))				{					id.ChangeIntValue(firstOperand.GetStringValue() < secondOperand.GetStringValue());				}				else					throw ExecutorException();				argsStack.Push(id);				break;			}			case LEXEME_LESS_OR_EQUAL:			{				auto secondOperand = argsStack.Pop(), firstOperand = argsStack.Pop();				Identifier id;				id.ChangeType(INT);				if ((firstOperand.GetType() == INT) && (secondOperand.GetType() == INT))				{					id.ChangeIntValue(firstOperand.GetIntValue() <= secondOperand.GetIntValue());				}				else if ((firstOperand.GetType() == INT) && (secondOperand.GetType() == REAL))				{					id.ChangeIntValue(firstOperand.GetIntValue() <= secondOperand.GetRealValue());				}				else if ((firstOperand.GetType() == REAL) && (secondOperand.GetType() == INT))				{					id.ChangeIntValue(firstOperand.GetRealValue() <= secondOperand.GetIntValue());				}				else if ((firstOperand.GetType() == REAL) && (secondOperand.GetType() == REAL))				{					id.ChangeIntValue(firstOperand.GetRealValue() <= secondOperand.GetRealValue());				}				else if ((firstOperand.GetType() == STRING) && (secondOperand.GetType() == STRING))				{					id.ChangeIntValue(firstOperand.GetStringValue() <= secondOperand.GetStringValue());				}				else					throw ExecutorException();				argsStack.Push(id);				break;			}			case LEXEME_NOT_EQUAL:			{				auto secondOperand = argsStack.Pop(), firstOperand = argsStack.Pop();				Identifier id;				id.ChangeType(INT);				if ((firstOperand.GetType() == INT) && (secondOperand.GetType() == INT))				{					id.ChangeIntValue(firstOperand.GetIntValue() != secondOperand.GetIntValue());				}				else if ((firstOperand.GetType() == INT) && (secondOperand.GetType() == REAL))				{					id.ChangeIntValue(firstOperand.GetIntValue() != secondOperand.GetRealValue());				}				else if ((firstOperand.GetType() == REAL) && (secondOperand.GetType() == INT))				{					id.ChangeIntValue(firstOperand.GetRealValue() != secondOperand.GetIntValue());				}				else if ((firstOperand.GetType() == REAL) && (secondOperand.GetType() == REAL))				{					id.ChangeIntValue(firstOperand.GetRealValue() != secondOperand.GetRealValue());				}				else if ((firstOperand.GetType() == STRING) && (secondOperand.GetType() == STRING))				{					id.ChangeIntValue(firstOperand.GetStringValue() != secondOperand.GetStringValue());				}				else					throw ExecutorException();				argsStack.Push(id);				break;			}			case LEXEME_EQUAL:			{				auto secondOperand = argsStack.Pop(), firstOperand = argsStack.Pop();				Identifier id;				id.ChangeType(INT);				if ((firstOperand.GetType() == INT) && (secondOperand.GetType() == INT))				{					id.ChangeIntValue(firstOperand.GetIntValue() == secondOperand.GetIntValue());				}				else if ((firstOperand.GetType() == INT) && (secondOperand.GetType() == REAL))				{					id.ChangeIntValue(firstOperand.GetIntValue() == secondOperand.GetRealValue());				}				else if ((firstOperand.GetType() == REAL) && (secondOperand.GetType() == INT))				{					id.ChangeIntValue(firstOperand.GetRealValue() == secondOperand.GetIntValue());				}				else if ((firstOperand.GetType() == REAL) && (secondOperand.GetType() == REAL))				{					id.ChangeIntValue(firstOperand.GetRealValue() == secondOperand.GetRealValue());				}				else if ((firstOperand.GetType() == STRING) && (secondOperand.GetType() == STRING))				{					id.ChangeIntValue(firstOperand.GetStringValue() == secondOperand.GetStringValue());				}				else					throw ExecutorException();				argsStack.Push(id);				break;			}			case LEXEME_AND:			{				auto secondOperand = argsStack.Pop(), firstOperand = argsStack.Pop();				Identifier id;				id.ChangeType(INT);				if ((firstOperand.GetType() == INT) && (secondOperand.GetType() == INT))				{					id.ChangeIntValue(firstOperand.GetIntValue() && secondOperand.GetIntValue());				}				else if ((firstOperand.GetType() == INT) && (secondOperand.GetType() == REAL))				{					id.ChangeIntValue(firstOperand.GetIntValue() && secondOperand.GetRealValue());				}				else if ((firstOperand.GetType() == REAL) && (secondOperand.GetType() == INT))				{					id.ChangeIntValue(firstOperand.GetRealValue() && secondOperand.GetIntValue());				}				else if ((firstOperand.GetType() == REAL) && (secondOperand.GetType() == REAL))				{					id.ChangeIntValue(firstOperand.GetRealValue() && secondOperand.GetRealValue());				}				else					throw ExecutorException();				argsStack.Push(id);				break;			}			case LEXEME_OR:			{				auto secondOperand = argsStack.Pop(), firstOperand = argsStack.Pop();				Identifier id;				id.ChangeType(INT);				if ((firstOperand.GetType() == INT) && (secondOperand.GetType() == INT))				{					id.ChangeIntValue(firstOperand.GetIntValue() || secondOperand.GetIntValue());				}				else if ((firstOperand.GetType() == INT) && (secondOperand.GetType() == REAL))				{					id.ChangeIntValue(firstOperand.GetIntValue() || secondOperand.GetRealValue());				}				else if ((firstOperand.GetType() == REAL) && (secondOperand.GetType() == INT))				{					id.ChangeIntValue(firstOperand.GetRealValue() || secondOperand.GetIntValue());				}				else if ((firstOperand.GetType() == REAL) && (secondOperand.GetType() == REAL))				{					id.ChangeIntValue(firstOperand.GetRealValue() || secondOperand.GetRealValue());				}				else					throw ExecutorException();				argsStack.Push(id);				break;			}			case LEXEME_NOT:			{				auto operand = argsStack.Pop();				Identifier id;				id.ChangeType(INT);				if (operand.GetType() == INT)				{					id.ChangeIntValue(!operand.GetIntValue());					argsStack.Push(id);				}				else					throw ExecutorException();				break;			}			case LEXEME_UNARY_MINUS:			{				auto operand = argsStack.Pop();				if (operand.GetType() == INT)				{					operand.ChangeIntValue(operand.GetIntValue() * (-1));				}				else if (operand.GetType() == INT)				{					operand.ChangeRealValue(operand.GetRealValue() * (-1));				}				else					throw ExecutorException();				argsStack.Push(operand);				break;			}			case RPM_LABEL:			{				if (program[counter + 1].GetType() == RPM_GOTO)				{					counter = program[counter].GetValue();					--counter; // it will be increased cuz of the loop				}				else if(program[counter + 1].GetType() == RPM_FALSE_GOTO)				{					if (argsStack.Pop().GetIntValue() == 0)						counter = program[counter].GetValue() - 1; // it will be increased cuz of the loop					else						++counter;				}				break;			}			case LEXEME_READ:			{				auto operand = argsStack.Pop();				if (Parser::structuresVector[operand.GetIntValue()][operand.GetRealValue()].GetType() == INT)				{					int n;					cin >> n;					Parser::structuresVector[operand.GetIntValue()][operand.GetRealValue()].ChangeIntValue(n);				}				else if (Parser::structuresVector[operand.GetIntValue()][operand.GetRealValue()].GetType() == REAL)				{					double v;					cin >> v;					Parser::structuresVector[operand.GetIntValue()][operand.GetRealValue()].ChangeRealValue(v);				}				else if (Parser::structuresVector[operand.GetIntValue()][operand.GetRealValue()].GetType() == STRING)				{					String str;					cin >> str;					Parser::structuresVector[operand.GetIntValue()][operand.GetRealValue()].ChangeStringValue(str);				}				else					throw ExecutorException();				break;			}			case LEXEME_WRITE:			{				Identifier operand;				std::deque<Identifier> queue;				while (!argsStack.IsEmpty())				{					queue.push_back(argsStack.Pop());				}				while (!queue.empty())				{					operand = queue.back();					queue.pop_back();					if (operand.GetType() == INT)						cout << operand.GetIntValue() << endl;					else if (operand.GetType() == REAL)						cout << operand.GetRealValue() << endl;					else if (operand.GetType() == STRING)						cout << operand.GetStringValue() << endl;					else						ExecutorException();				}				break;							}			case RPM_ADDRESS:			{				Identifier id;				id.ChangeType(USER);				id.ChangeIntValue(currentLexeme.GetTableNumber());				id.ChangeRealValue(currentLexeme.GetValue());				argsStack.Push(id);				break;			}			case LEXEME_ASSIGNMENT:			{				auto second = argsStack.Pop(), firstAddress = argsStack.Pop();				Identifier& first = Parser::structuresVector[firstAddress.GetIntValue()][firstAddress.GetRealValue()];				if ((first.GetType() == INT) && (second.GetType() == INT))				{					first.ChangeIntValue(second.GetIntValue());				}				else if ((first.GetType() == INT) && (second.GetType() == REAL))				{					first.ChangeIntValue(static_cast<int>(second.GetRealValue()));				}				else if ((first.GetType() == REAL) && (second.GetType() == REAL))				{					first.ChangeRealValue(second.GetRealValue());				}				else if ((first.GetType() == REAL) && (second.GetType() == INT))				{					first.ChangeRealValue(second.GetIntValue());				}				else if ((first.GetType() == STRING) && (second.GetType() == STRING))				{					first.ChangeStringValue(second.GetStringValue());				}				else if((first.GetType() == USER) && (second.GetType() == USER))				{					Parser::structuresVector[first.GetIntValue()] = Parser::structuresVector[second.GetIntValue()];				}				else					throw ExecutorException();				argsStack.Push(first);				break;			}			case RPM_OUT_OF_STACK:			{				argsStack.Pop();				break;			}			default:				throw ExecutorException();		}	}}
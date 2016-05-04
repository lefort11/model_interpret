
#include "../Lexeme.h"


/* pshe pshe pshe */

class ReversePolishNotation
{
	Lexeme* pointer;
	int size;
	int freeElementNumber; //number of the frst

public:
	ReversePolishNotation(int maxSize = 0): pointer(new Lexeme[size = maxSize]), freeElementNumber(0) {}
	~ReversePolishNotation()
	{
		delete[] pointer;
	}

	class RPMException {};

	void AddLexeme(Lexeme lexeme)
	{
		if(freeElementNumber == size)
			throw RPMException();
		pointer[freeElementNumber] = lexeme;
		++freeElementNumber;
	}

	void AddLexeme(Lexeme lexeme, int position)
	{
		if(position >= size)
			throw RPMException();
		pointer[position] = lexeme;
	}

	bool IsFull() const
	{
		return freeElementNumber == size;
	}

	int GetFreeElementNumber() const
	{
		return freeElementNumber;
	}

	Lexeme const& operator[](int position) const
	{
		if(position >= size)
			throw RPMException();
		return pointer[position];
	}

	Lexeme& operator[](int position)
	{
		if(position >= size)
			throw RPMException();
		return pointer[position];
	}

	void PutBlank()
	{
		++freeElementNumber;
	}

	int SearchForFirstFalseGoto() const
	{
		auto counter = GetFreeElementNumber();
		while (pointer[counter] != RPM_FALSE_GOTO)
			--counter;
		return counter;
	}

	int SearchForFirstLoop() const
	{
		auto counter = GetFreeElementNumber();
		while(pointer[counter] != RPM_LOOP)
			--counter;
		return counter;
	}

};
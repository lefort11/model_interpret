#pragma once

template <class T>
class Stack
{
	T* pointer;
	int top;
	int size;

public:
	Stack(int maxSize): pointer(new T[maxSize]), top(0), size(maxSize) {}

	Stack(Stack const& other)
	{
		top = other.top;
		size = other.size;
		pointer = new T[size];
		for(int i = 0; i < top; ++i)
			pointer[i] = other.pointer[i];
	}

	~Stack()
	{
		delete[] pointer;
	}

	class StackException {};

	bool IsFull() const
	{
		return top == size;
	}

	void Push(T element)
	{
		if(IsFull()) // reallocating memory
		{
			size *= 2;
			T* anotherPtr = new T[size];
			for(int i = 0; i < size; ++i)
				anotherPtr[i] = pointer[i];
			delete[] pointer;
			pointer = anotherPtr;
		}
		pointer[top++] = element;
	}

	bool IsEmpty() const
	{
		return top == 0;
	}

	T& Pop()
	{
		if(IsEmpty())
			throw StackException();
		return pointer[--top];
	}


	void Clear()
	{
		top = 0;
	}
};
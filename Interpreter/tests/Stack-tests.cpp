#include "../Stack.h"
#include "testing.h"
#include <iostream>

TEST(stackTests)
		{

			Stack <int> stack(10);
			for(int i = 0; i < 20; ++i)
				stack.Push(i);
			for(int i = 19; !stack.IsEmpty(); --i)
			{
				assert(stack.Pop() == i);
			}
			Stack <int> stack2(stack);
			stack.Clear();
			for(int i = 19; !stack2.IsEmpty(); --i)
			{
				assert(stack2.Pop() == i);
			}
		};
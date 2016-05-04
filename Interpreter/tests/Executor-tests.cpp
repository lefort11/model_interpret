#include "testing.h"
#include "../Parser.h"
#include "../Executor.h"

/*TEST(executorTests)
		{
			Parser parser("/Users/Gleb/Desktop/model_interpret/Interpreter/tests/test3.txt");
			parser.Analyze();
			Executor executor;
			executor.Execute(parser.program);

		}; */

TEST(executorTests2)
		{
			Parser parser("/Users/Gleb/Desktop/model_interpret/Interpreter/tests/test3.txt");
			parser.Analyze();
			Executor executor;
			executor.Execute(parser.program);


		};
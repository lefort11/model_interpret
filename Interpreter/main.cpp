#include <iostream>

#include "Scanner/Scanner.h"
#include "Parser/Parser.h"
#include "Executor/Executor.h"

using namespace std;


int main()
{

		cout << "Enter the file path" << endl;
		char filepath[100];
		cin >> filepath;
		Parser parser(filepath);
		Executor executor;
		parser.Analyze();
		executor.Execute(parser.program);

	/*catch(Scanner::ScannerException)
	{
		cout << "Lexical error" << endl;
	}
	catch(Parser::ParserException)
	{
		cout << "Syntax error" << endl;
	}
	catch(Preprocessor::PPException)
	{
		cout << "Preprocessing error" << endl;
	}
	catch(Executor::ExecutorException)
	{
		cout << "Execution error" << endl;
	} */
	return 0;
}
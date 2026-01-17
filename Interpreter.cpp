#include "Type.h"
#include "InterpreterException.h"
#include "SyntaxException.h"
#include "Parser.h"
#include <iostream>

#define WELCOME "Welcome to Magshimim Python Interperter version 1.0 by "
#define YOUR_NAME "Roei"


int main(int argc,char **argv)
{
	std::cout << WELCOME << YOUR_NAME << std::endl;

	std::string input_string;

	// get new command from user
	std::cout << ">>> ";
	std::getline(std::cin, input_string);
	
	while (input_string != "quit()")
	{
		Type* type_ = nullptr;
		try 
		{
			type_ = Parser::parseString(input_string);

			if (type_->isPrintable())
			{
				std::cout << type_->toString() << std::endl;
			}
			if (type_->getIsTemp())
			{
				delete type_;
			}
		}
		catch (std::exception& e) {
			std::cout << e.what() << std::endl;
			delete type_;
		}
		// parsing command
		


		// get new command from user
		std::cout << ">>> ";
		std::getline(std::cin, input_string);
	}

	Parser::clearMemory();
	return 0;
}

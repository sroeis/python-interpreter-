#pragma once
#include "InterpreterException.h"
#include "IndentationException.h"
#include "SyntaxException.h"
#include "NameErrorException.h"
#include "TypeException.h"
#include "Type.h"
#include "integer.h"
#include "boolean.h"
#include "void.h"
#include "string.h"
#include "List.h"
#include "Function.h"
#include "Helper.h"
#include <string>
#include <unordered_map>
#include <iostream>
#include <sstream>


class Parser
{
public:
	static Type* parseString(std::string str);
	static Type* getType(std::string& str);
	static void clearMemory();


private:
	static bool isLegalVarName(std::string& str);
	static bool makeAssignment(std::string& str);
	static Type* getVariableValue(std::string& str);
	static std::unordered_map<std::string, std::shared_ptr<Type>> _variables;

};

#include "Parser.h"
#include <iostream>
#define TAB "\t"
std::unordered_map<std::string, std::unique_ptr<Type>> Parser::_variables;
Type* Parser::parseString(std::string str)
{
	if (str.at(0) == *TAB || str.at(0) == ' ')
	{
		throw IndentationException();
	}
	Helper::trim(str);
	Type* type = getVariableValue(str);
	if (type == nullptr)
	{
		type = getType(str);
		if (type != nullptr)
		{
			return type;
		}
		else
		{
			if (makeAssignment(str))
			{
				return new Void(true);
			}// if not true throws syntax error.
			else {
				throw SyntaxException();
			}
		}
	}
	else {
		return type;
	}
}

Type* Parser::getType(std::string& str)
{
	if (Helper::isBoolean(str))
	{
		bool val;
		if (str == "false")
		{
			val = false;
		}
		else {
			val = true;
		}
		return new Boolean(val,true);
	}
	else if (Helper::isInteger(str))
	{
		Helper::removeLeadingZeros(str);
		return new Integer(stoi(str), true);
	}
	else if (Helper::isString(str))
	{
		return new String(str, true);
	}
	else {
		return nullptr;
	}
}

bool Parser::isLegalVarName(std::string& str)
{
	if (!Helper::isDigit(str.at(0)))
	{
		for (auto i : str)
		{
			if (Helper::isDigit(i) || Helper::isLetter(i) || Helper::isUnderscore(i))
			{
				continue;
			}
			else {
				return false;
			}
		}
		return true;
	}
	return false;
}

bool Parser::makeAssignment(std::string& str)
{
	size_t equalIndex = str.find('=');

	if (equalIndex != std::string::npos && equalIndex != str.size() - 1 && equalIndex > 0)
	{
		std::string varName = str.substr(0, equalIndex);;
		std::string varValue = str.substr(equalIndex + 1);;

		Helper::trim(varValue);
		Helper::trim(varName);
		Type* type = getType(varValue);
		if (!isLegalVarName(varName) || type == nullptr)
		{
			//check only if type is null and  if the name is not wrong
			if (type == nullptr && isLegalVarName(varName)) 
			{
				// check if the right var is a valid name
				if (isLegalVarName(varValue))
				{
					Type* VarType = getVariableValue(varValue);

					// check if its actaully a variable
					if (VarType == nullptr)
					{
						// if no: name exception
						delete type;
						throw NameErrorException(varValue);
					}
					else {
						Type* deepCopy = VarType->clone();
						// if yes then assign varValue into varName (deep copy)
						_variables.insert_or_assign(varName, std::unique_ptr<Type>(deepCopy));
						return true;
					}
				}
			}
			delete type;
			throw SyntaxException();
		}
		type->setIsTemp(false);
		_variables.insert_or_assign(varName, std::unique_ptr<Type>(type));
		return true;
	}
	else if (equalIndex == std::string::npos)
	{
		throw NameErrorException(str);
	}
	else {
		return false;
	}
}

Type* Parser::getVariableValue(std::string& str)
{
	auto it = _variables.find(str);
	if (it != _variables.end())
	{
		return it->second.get();
	}
	else
	{
		return nullptr;
	}
}

void Parser::clearMemory()
{
	_variables.clear();
}
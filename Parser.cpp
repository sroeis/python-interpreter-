#include "Parser.h"
#include <iostream>
#define TAB "\t"
std::unordered_map<std::string, std::shared_ptr<Type>> Parser::_variables;
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
		if (str == "False")
		{
			val = false;
		}
		else if (str == "True") {
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
	else if (Helper::isList(str))
	{
		std::vector<Type*> TempElements;
		// empty list
		if (str.size() == 2)
		{
			return new List(TempElements, true);
		}
		bool run = true;
		size_t Start_Pos = 1;
		size_t Comma_Pos = 1;
		std::string temp;
		while (run)
		{
			Comma_Pos = str.find(",", Start_Pos);
			if (Comma_Pos == std::string::npos)
			{
				run = false;
				temp = str.substr(Start_Pos);
				temp.pop_back();
			}
			else {
				temp = str.substr(Start_Pos, Comma_Pos - Start_Pos);
				Start_Pos = Comma_Pos + 1;
			}

			Helper::trim(temp);
			TempElements.push_back(getType(temp));
		}
		return new List(TempElements, true);

	}
	else if (Helper::isFunc(str)) 
	{
		// if were in here than that means we have something like this : type(......)   
		size_t P_Index = str.find("(");

		//getting whats in the parentheses
		std::string VarName = str.substr(P_Index + 1);// VarName = kamdkaida)
		Helper::rtrim(VarName);
		VarName.pop_back();

		if (VarName.empty())
		{
			throw SyntaxException();
		}
		//checking if its a variable
		Type* T = getVariableValue(VarName);
		if (T != nullptr)
		{
			return new Function(T->getKind());
		}
		else {
			T = getType(VarName);
			if (T != nullptr)
			{
				return new Function(T->getKind());
			}
			throw NameErrorException(VarName);
		}
	}
	else if (Helper::isDel(str))
	{
		std::string Sub = str.substr(3);//if del ..... so ( .....) onwards
		Helper::trim(Sub);
		if (Sub.empty())
		{
			throw SyntaxException();
		}
		Type* T = getVariableValue(Sub);
		if (T != nullptr)
		{
			_variables.erase(Sub);
			return new Void(true);
		}
		else {
			throw NameErrorException(Sub);
		}

	}
	else if (Helper::isLen(str))
	{
		if (str == "len")
		{
			return new Function(TypeKind::Len);
		}

		size_t P_Index = str.find("(");
		size_t PR_Index = str.find(")");
		if (P_Index == std::string::npos || PR_Index == std::string::npos)
		{
			throw SyntaxException();
		}

		std::string Sub = str.substr(P_Index + 1);
		Sub.pop_back();
		Type* T = getVariableValue(Sub);
		size_t size = 0;
		if (T != nullptr)
		{
			auto kind = T->getKind();
			if (kind == TypeKind::List || kind == TypeKind::Str)
			{
				if (auto* Seq = dynamic_cast<Sequence*>(T))
				{
					size = Seq->getSize();
					return new Integer(size, true);
				}
				else{}
			}
			else {
				throw TypeException(kind);
			}
		}
		else {
			throw NameErrorException(Sub);
		}

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
		if (Helper::isFunc(varValue) || Helper::isDel(varValue) )
		{
			throw SyntaxException();
		}
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
						
						if (VarType->isList())
						{
							_variables.insert_or_assign(varName, std::shared_ptr<Type>(VarType));
						}
						else {
							Type* deepCopy = VarType->clone();
							// if yes then assign varValue into varName (deep copy)
							_variables.insert_or_assign(varName, std::shared_ptr<Type>(deepCopy));
						}
						return true;

					}
				}
			}
			delete type;
			throw SyntaxException();
		}
		type->setIsTemp(false);
		_variables.insert_or_assign(varName, std::shared_ptr<Type>(type));
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
#pragma once
#include "InterpreterException.h"
#include <string>

class NameErrorException : public InterpreterException
{
public:
	NameErrorException(std::string& val);
	virtual const char* what() const noexcept;

private:
	std::string _name;
	std::string _msg;
};
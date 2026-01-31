#pragma once
#include "InterpreterException.h"
#include"Type.h"
#include <string>

class TypeException : public InterpreterException
{
public:
	TypeException(TypeKind& kind);
	virtual const char* what() const noexcept;

private:
	std::string _type;
	std::string _msg;
};
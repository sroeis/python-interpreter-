#include "NameErrorException.h"

NameErrorException::NameErrorException(std::string& val)
{

	_name = val;
	_msg = "NameError : name \'" + _name + " \' is not defined";

}

const char* NameErrorException::what() const noexcept
{
	return _msg.c_str();
}

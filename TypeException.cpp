#include "TypeException.h"

TypeException::TypeException(TypeKind& kind)
{
    switch (kind)
    {
    case TypeKind::Int:
        _type = "int";
        break;
    case TypeKind::Str:
        _type = "str";
        break;
    case TypeKind::Bool:
        _type = "bool";
        break;
    case TypeKind::List:
        _type = "list";
        break;
    case TypeKind::Len:
        _type = "len";
        break;
    }
	_msg = "TypeError: object of type \'" + _type + "\' has no len()";
}

const char* TypeException::what() const noexcept
{
    return _msg.c_str();
}

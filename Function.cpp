#include "Function.h"

Function::Function(const TypeKind val)
{
    setIsTemp(true);

    switch (val) 
    {
        case TypeKind::Int:
            _value = "int";
            break;
        case TypeKind::Str:
            _value = "str";
            break;
        case TypeKind::Bool:
            _value = "bool";
            break;
        case TypeKind::List:
            _value = "list";
            break;
        case TypeKind::Len:
            _value = "len";
            break;
        default:
            throw SyntaxException();
    }

}

const bool Function::isPrintable()
{
    return true;
}

const std::string Function::toString()
{
    if (_value == "len")
    {
        return "<built-in function len>";
    }
    return "<type '" + _value + "'>";
}

Type* Function::clone() const
{
    return nullptr;
}

const bool Function::isList()
{
    return false;
}

const TypeKind Function::getKind()
{
    return TypeKind::Function;
}

#include "boolean.h"

Boolean::Boolean(bool val, bool temp)
{
    _value = val;
    setIsTemp(temp);
}

const bool Boolean::isPrintable()
{
    return true;
}

const std::string Boolean::toString()
{
    switch (_value) 
    {
        case true:
            return "true";

        case false:
            return "false";
    }
   
}

Boolean* Boolean::clone() const
{
    return new Boolean(*this);
}

const bool Boolean::isList()
{
    return false;
}

const TypeKind Boolean::getKind()
{
    return TypeKind::Bool;
}

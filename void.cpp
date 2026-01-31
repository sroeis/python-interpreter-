#include "void.h"

Void::Void(bool temp)
{
   setIsTemp(temp);
}

const bool Void::isPrintable()
{
    return false;
}

const std::string Void::toString()
{
    return " ";
}

Void* Void::clone() const
{
    return new Void(*this);
}

const bool Void::isList()
{
    return false;
}

const TypeKind Void::getKind()
{
    return TypeKind::Void;
}

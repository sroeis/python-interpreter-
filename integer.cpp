#include "integer.h"

Integer::Integer(int val, bool temp)
{
    _value = val;
    setIsTemp(temp);
}

const bool Integer::isPrintable()
{
    return true;
}

const std::string Integer::toString()
{
    return  std::to_string(_value);
}

Type* Integer::clone() const
{
    return new Integer(*this);
}

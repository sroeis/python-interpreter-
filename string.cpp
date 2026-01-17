#include "string.h"

String::String(std::string val, bool temp)
{
    _value = val;
    setIsTemp(temp);
}

const bool String::isPrintable()
{
    return true;
}

const std::string String::toString()
{
    std::string s;
    if(_value.find('\'') == std::string::npos) 
    {
        if (_value.at(_value.size() - 1) == '\"' && _value.at(0) == '\"')
        {
            _value.erase(0, 1);
            _value.pop_back();
        }

        s = "\'" + _value + "\'";
        return s;

    }else{
        return _value;
    }
}

String* String::clone() const
{
    return new String(*this);
}

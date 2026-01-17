#pragma once
#include "Type.h"

class Integer : public Type 
{
public:

	Integer(int val, bool temp);

	const bool isPrintable() override;
	const std::string toString() override;
	Type* clone() const override;

private:
	int _value;
};
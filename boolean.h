#pragma once
#include "Type.h"

class Boolean : public Type
{
public:
	Boolean(bool val, bool temp);
	const bool isPrintable() override;
	const std::string toString() override;
	Boolean* clone() const override;

private:
	bool _value;
};
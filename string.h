#pragma once
#include "sequence.h"

class String : public Sequence
{
public:
	String(std::string val, bool temp);
	const bool isPrintable() override;
	const std::string toString() override;
	String* clone() const override;

private:
	std::string _value;
};
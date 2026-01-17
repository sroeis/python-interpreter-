#pragma once
#include "Type.h"

class Void : public Type
{
public:
	Void(bool temp);
	const bool isPrintable() override;
	const std::string toString() override;
	Void* clone() const override;


};
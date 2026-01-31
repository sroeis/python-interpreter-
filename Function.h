#pragma once
#include "Type.h"
#include "SyntaxException.h"
class Function : public Type
{
public:
	Function() = default;
	Function(const TypeKind val);
	const bool isPrintable() override;
	const std::string toString() override;
	Type* clone() const override;
	const bool isList() override;
	const TypeKind getKind() override;

private:
	std::string _value;
};
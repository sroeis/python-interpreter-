#pragma once
#include <string>
enum class TypeKind {
	Int,
	Str,
	Bool,
	List,
	Function,
	Void,
	Len
};
class Type
{
public:
	Type() =  default;
	virtual ~Type() = default;

	bool getIsTemp();
	void setIsTemp(bool val);
	virtual const bool isPrintable() = 0;
	virtual const std::string toString() = 0;
	virtual Type* clone() const = 0;
	virtual const bool isList() = 0;
	virtual const TypeKind getKind() = 0;
private:
	bool _isTemp = false;
};

#pragma once
#include "sequence.h"
#include <vector>
#include <iostream>
class List : public Sequence
{
public:
	List(std::vector<Type*>& TempElements, bool isTemp);
	const bool isPrintable() override;
	const std::string toString() override;
	List* clone() const override;
	const bool isList() override;
	const TypeKind getKind() override;
	size_t getSize();

private:
	std::vector<Type*> _elements;
};
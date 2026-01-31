#include "List.h"

List::List(std::vector<Type*>& TempElements, bool isTemp)
	:_elements(TempElements)
{
	setIsTemp(isTemp);
}

const bool List::isPrintable()
{
	return true;
}

const std::string List::toString()
{
	std::string result = "[";
	for (size_t i = 0; i < _elements.size() ; i++)
	{
		result += _elements.at(i)->toString() + ", ";
	}
	result.erase(result.size() - 2);
	result += "]";
	

	return result;
}

List* List::clone() const
{
	return nullptr;
}

const bool List::isList()
{
	return true;
}

const TypeKind List::getKind()
{
	return TypeKind::List;
}

size_t List::getSize()
{
	return _elements.size();
}

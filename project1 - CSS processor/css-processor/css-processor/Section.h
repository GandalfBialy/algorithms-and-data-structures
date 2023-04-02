#pragma once


#include "List.h"
#include "Declaration.h"


class Section
{
private:
	List<String> selectors;
	List<Declaration> declarations;

public:
	void setSelectors(List<String> selectors);
	void setDeclarations(List<Declaration> declarations);
};


#pragma once


#include "List.h"
#include "Declaration.h"


class Section
{
private:
	String sectionName;
	List<String> selectors;
	List<Declaration> declarations;

public:
	Section();
	Section(String sectionName);

	void print();
	
	void setSelectors(List<String> selectors);
	void setDeclarations(List<Declaration> declarations);

	String getSectionName();
	List<String> getSelectors();
	List<Declaration> getDeclarations();
};


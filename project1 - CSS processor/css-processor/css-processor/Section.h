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

	void appendDeclaration(Declaration declaration);

	void removeProperty(String propertyName);
	
	void setSelectors(List<String> selectors);

	String getSectionName() const;
	List<String> getSelectors() const;
	List<String>* getSelectorsPointer();
	List<Declaration> getDeclarations() const;
};

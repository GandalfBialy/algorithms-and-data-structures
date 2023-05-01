#pragma once


#include "List.h"
#include "Declaration.h"


class Section
{
private:
	String sectionName;
	List<String> selectors;
	List<Declaration> declarations;

	bool hasNoSelectors = true;

public:
	Section();
	Section(String sectionName);

	void print();

	void appendDeclaration(Declaration declaration);

	int findProperty(String propertyName);
	void replaceDeclarationValue(int declarationIndex, String valueName);
	void removeProperty(String propertyName);
	
	bool isEmpty() const;

	void setSelectors(List<String> selectors);
	void setHasNoSelectors(bool hasNoSelectors);

	String getSectionName() const;
	List<String> getSelectors() const;
	List<String>* getSelectorsPointer();
	List<String> getProperties() const;
	List<Declaration> getDeclarations() const;
	bool getHasNoSelectors() const;
};

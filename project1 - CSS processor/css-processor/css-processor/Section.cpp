#include "Section.h"


Section::Section() :
	sectionName(""),
	hasNoSelectors(false),
	selectors(List<String>()),
	declarations(List<Declaration>()) {
}


Section::Section(String sectionName) :
	sectionName{ sectionName },
	hasNoSelectors{ false },
	selectors{ List<String>() },
	declarations{ List<Declaration>() } {
}


void Section::print() {
	std::cerr << "Section: " << sectionName << std::endl;

	std::cerr << "Selectors:" << std::endl;
	for (int i = 0; i < selectors.getSize(); i++) {
		std::cerr << selectors[i] << std::endl;
	}
	std::cerr << std::endl;

	std::cerr << "Declarations:" << std::endl;
	for (int i = 0; i < declarations.getSize(); i++) {
		std::cerr << declarations[i].getProperty() << ": " << declarations[i].getValue() << std::endl;
	}
	std::cerr << "----------" << std::endl;
}


void Section::appendDeclaration(Declaration declaration) {
	declarations.append(declaration);
}


int Section::findProperty(String propertyName) {
	if (declarations.getSize() == 0) {
		return -1;
	}

	Node<Declaration>* declaration = declarations.getHead();
	int index = 0;

	while (declaration != nullptr) {
		if (declaration->data.getProperty() == propertyName) {
			return index;
		}

		declaration = declaration->next;
		index++;
	}

	return -1;
}


void Section::replaceDeclarationValue(int declarationIndex, String valueName) {
	declarations[declarationIndex].setValue(valueName);
}


void Section::removeProperty(String propertyName) {
	int index = findProperty(propertyName);

	if (index != -1 and declarations.getSize() != 0 and declarations.getSize() > index) {
		declarations.removeAt(index);
	}

	if (declarations.getSize() == 0) {
		sectionName = "";
	}
}


bool Section::isEmpty() const {
	return declarations.getSize() == 0;
}


void Section::setSelectors(List<String> selectors) {
	this->selectors = selectors;
}


void Section::setHasNoSelectors(bool hasNoSelectors) {
	this->hasNoSelectors = hasNoSelectors;
}


String Section::getSectionName() const {
	return sectionName;
}


List<String> Section::getSelectors() const {
	return selectors;
}


List<String>* Section::getSelectorsPointer() {
	return &selectors;
}


List<String> Section::getProperties() const {
	List<String> properties;

	for (int i = 0; i < declarations.getSize(); i++) {
		properties.append(declarations[i].getProperty());
	}	

	return properties;
}


List<Declaration> Section::getDeclarations() const {
	return declarations;
}


bool Section::getHasNoSelectors() const {
	return hasNoSelectors;
}

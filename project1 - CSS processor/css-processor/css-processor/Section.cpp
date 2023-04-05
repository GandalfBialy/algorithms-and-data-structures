#include "Section.h"


Section::Section() {
	sectionName = "";
	selectors = List<String>();
	declarations = List<Declaration>();
}


Section::Section(String sectionName) {
	this->sectionName = sectionName;
	selectors = List<String>();
	declarations = List<Declaration>();
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


// TODO: PERFORMANCE ISSUE, USE LIST METHODS
void Section::removeProperty(String propertyName) {
	int declarationIndex = -1;

	for (int declarationIndex = 0; declarationIndex < declarations.getSize(); declarationIndex++) {
		if (declarations[declarationIndex].getProperty() == propertyName) {
			declarations.removeAt(declarationIndex);
		}
	}

	declarations.removeAt(declarationIndex);

	if (declarations.getSize() == 0) {
		sectionName = "";
	}
}


void Section::setSelectors(List<String> selectors) {
	this->selectors = selectors;
}


void Section::setDeclarations(List<Declaration> declarations) {
	this->declarations = declarations;
}


String Section::getSectionName() {
	return sectionName;
}


List<String> Section::getSelectors() {
	return selectors;
}


List<Declaration> Section::getDeclarations() {
	return declarations;
}

#include "CSS.h"


CSS::CSS() {
	sections = List<Section>();
}


void CSS::appendSection(Section section) {
	sections.append(section);
}


void CSS::printCSS() {
	std::cerr << "--- PRINTING CSS SECTIONS ---" << std::endl;
	
	for (int i = 0; i < sections.getSize(); i++) {
		sections[i].print();
		std::cerr << std::endl;
	}
}


void CSS::removeSection(int sectionIndex) {
	sections.removeAt(sectionIndex);
}


// TODO: PERFORMANCE ISSUE, USE LIST METHODS
void CSS::removeProperty(int sectionIndex, String propertyName) {
	sections[sectionIndex].removeProperty(propertyName);

	// if section declarations list is empty, delete section
	if (sections[sectionIndex].getDeclarations().getSize() == 0) {
		sections.removeAt(sectionIndex);
	}
}


void CSS::setSections(List<Section> sections) {
	this->sections = sections;
}


List<Section> CSS::getSections() {
	return sections;
}


int CSS::getSectionsCount() {
	return sections.getSize();
}

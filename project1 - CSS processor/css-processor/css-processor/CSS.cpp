#include "CSS.h"


CSS::CSS() {
	sections = List<Section>();
}


void CSS::appendSection(Section section) {
	sections.append(section);
}


void CSS::printCSS() {
	std::cerr << "--- PRINTING CSS SECTIONS ---" << std::endl;
	
	Node<Section>* section = sections.getHead();

	while (section != nullptr) {
		section->data.print();
		section = section->next;
	}
}


void CSS::removeSection(int sectionIndex) {
	sections.removeAt(sectionIndex);
}


void CSS::removeProperty(int sectionIndex, String propertyName) {
	sections[sectionIndex].removeProperty(propertyName);

	if (sections[sectionIndex].getDeclarations().getSize() == 0) {
		sections.removeAt(sectionIndex);
	}
}


List<Section> CSS::getSections() const {
	return sections;
}


int CSS::getSectionsCount() {
	return sections.getSize();
}

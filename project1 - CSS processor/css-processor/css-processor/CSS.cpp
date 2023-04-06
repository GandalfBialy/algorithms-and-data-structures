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


void CSS::removeSection(int sectionIndex, String commandName) {
	// check if the section exists
	std::cerr << "removeSection: " << sectionIndex << std::endl;
	if (sectionIndex < 0 or sectionIndex >= sections.getSize()) {
		return;
	}
	
	sections.removeAt(sectionIndex);
	std::cout << commandName << " == " << "deleted\n";
}


void CSS::removeProperty(int sectionIndex, String propertyName, String commandName) {
	if (sectionIndex < 0 or sectionIndex >= sections.getSize()) {
		return;
	}

	int propertyIndex = sections[sectionIndex].findProperty(propertyName);

	if (propertyIndex < 0 or propertyIndex >= sections[sectionIndex].getDeclarations().getSize()) {
		return;
	}

	sections[sectionIndex].removeProperty(propertyName);

	std::cout << commandName << " == " << "deleted\n";

	if (sections[sectionIndex].getDeclarations().getSize() == 0 or sections[sectionIndex].getSelectors().getSize() == 0 or sections[sectionIndex].getSectionName() == "") {
		sections.removeAt(sectionIndex);
	}
}


List<Section> CSS::getSections() const {
	return sections;
}


int CSS::getSectionsCount() {
	return sections.getSize();
}

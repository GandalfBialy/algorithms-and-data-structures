#include "CSS.h"


void CSS::appendSection(Section section) {
	sections.append(section);
}


void CSS::printSections() {
	for (int i = 0; i < sections.getSize(); i++) {
		sections[i].print();
	}
}


void CSS::setSections(List<Section> sections) {
	this->sections = sections;
}


List<Section> CSS::getSections() {
	return sections;
}

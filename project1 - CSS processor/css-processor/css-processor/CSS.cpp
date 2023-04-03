#include "CSS.h"


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


void CSS::setSections(List<Section> sections) {
	this->sections = sections;
}


List<Section> CSS::getSections() {
	return sections;
}

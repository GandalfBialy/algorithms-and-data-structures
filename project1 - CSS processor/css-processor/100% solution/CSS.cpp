#include "CSS.h"


CSS::CSS() :
	sections{ List<Section>() },
	blockList{ BlockList<SECTIONS_PER_BLOCK>() },
	currentBlock{ nullptr },
	currentSectionIndex{ 0 } {
}


void CSS::appendSection(Section section) {
	sections.append(section);

	
	blockList.appendSection(section);

	/*if (currentBlock == nullptr) {
		currentBlock = new Block<SECTIONS_PER_BLOCK>();
		currentBlock->setSection(currentSectionIndex, section);
		currentSectionIndex++;
	}
	
	if (currentSectionIndex == SECTIONS_PER_BLOCK) {
		blockList.append(*currentBlock);
		currentBlock = new Block<SECTIONS_PER_BLOCK>();
		currentSectionIndex = 0;
	}*/

	
	/*std::cerr << "Block after: ";
	if (currentBlock != nullptr) {
		currentBlock->print();
	}
	else {
		std::cerr << "nullptr" << std::endl;
	}*/
}


void CSS::printCSS() {
	std::cerr << "--- PRINTING CSS SECTIONS ---" << std::endl;
	
	Node<Section>* section = sections.getHead();

	while (section != nullptr) {
		section->data.print();
		section = section->next;
	}


	blockList.print();
}


void CSS::removeSection(int sectionIndex, String commandName) {
	if (sectionIndex < 0 or sectionIndex >= sections.getSize()) {
		return;
	}
	
	sections.removeAt(sectionIndex);


	// block list below
	/*if (sectionIndex < 0 or sectionIndex >= blockList.getSectionsCount()) {
		return;
	}*/

	//blockList.removeSection(sectionIndex);

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

	if (isSectionEmpty(sectionIndex)) {
		sections.removeAt(sectionIndex);
	}




	// block section below
	/*if (sectionIndex < 0 or sectionIndex >= blockList.getSectionsCount()) {
		return;
	}

	auto& section = blockList.getSection(sectionIndex);
	section.removeProperty(propertyName);

	if (section.getProperties().isEmpty() or section.getSelectors().isEmpty() or section.getSectionName().isEmpty()) {
		blockList.removeSection(sectionIndex);
	}*/

	
	//std::cout << commandName << " == " << "deleted\n";
}


bool CSS::isSectionEmpty(int sectionIndex) {
	//sections[sectionIndex].getDeclarations().getSize() == 0 or sections[sectionIndex].getSelectors().getSize() == 0 or sections[sectionIndex].getSectionName() == "";
	
	
	if (sectionIndex < 0 or sectionIndex >= sections.getSize()) {
		return true;
	}

	return sections[sectionIndex].isEmpty();
}


List<Section> CSS::getSections() const {
	return sections;

	// block list below

	/*List<Section> allSections;
	BlockIterator<SECTIONS_PER_BLOCK> blockIt(blockList);

	for (auto& block : blockIt) {
		for (int i = 0; i < SECTIONS_PER_BLOCK; i++) {
			Section& section = block.getSection(i);

			if (!section.isEmpty()) {
				allSections.append(section);
			}
		}
	}

	return allSections;*/
}


int CSS::getSectionsCount() {
	return sections.getSize();

	//return blockList.getSectionsCount();
}


BlockList<SECTIONS_PER_BLOCK> CSS::getBlockList() const {
	return blockList;
}

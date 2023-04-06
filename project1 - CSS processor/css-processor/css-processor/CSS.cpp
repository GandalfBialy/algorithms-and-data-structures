#include "CSS.h"


CSS::CSS() :
	sections{ List<Section>() },
	blockList{ BlockList<SECTIONS_PER_BLOCK>() },
	currentBlock{ nullptr },
	currentSectionIndex{ 0 } {
}


void CSS::appendSection(Section section) {
	sections.append(section);

	
	/*std::cerr << "Block before: ";
	if (currentBlock != nullptr) {
		currentBlock->print();
	}
	else {
		std::cerr << "nullptr" << std::endl;
	}*/
	

	if (currentBlock == nullptr) {
		currentBlock = new Block<SECTIONS_PER_BLOCK>();
		// set sections in currentBlock
		currentBlock->setSection(currentSectionIndex, section);
		currentSectionIndex++;
	}
	
	if (currentSectionIndex == SECTIONS_PER_BLOCK) {
		blockList.append(*currentBlock);
		currentBlock = new Block<SECTIONS_PER_BLOCK>();
		currentSectionIndex = 0;
	}

	
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
}


void CSS::removeSection(int sectionIndex, String commandName) {
	// check if the section exists
	//std::cerr << "removeSection: " << sectionIndex << std::endl;
	if (sectionIndex < 0 or sectionIndex >= sections.getSize()) {
		return;
	}
	
	sections.removeAt(sectionIndex);
	std::cout << commandName << " == " << "deleted\n";



	// BLOCK LIST BELOW

	// remove section in block list
	//std::cerr << "removeSection: " << sectionIndex << std::endl;
	if (sectionIndex < 0 or sectionIndex >= blockList.getBlocks().getSize()) {
		return;
	}

	blockList.getBlocks().removeAt(sectionIndex);
	
	// decrease sectionsCounter
	//blockList.decrementSectionsCounter();

	//std::cout << commandName << " == " << "deleted\n";
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





	// remove property in block list
	//std::cerr << "removeProperty: " << sectionIndex << std::endl;
	if (sectionIndex < 0 or sectionIndex >= blockList.getBlocks().getSize()) {
		return;
	}

	// int
	propertyIndex = blockList.getBlocks()[sectionIndex].getSection(sectionIndex).findProperty(propertyName);
	
	if (propertyIndex < 0 or propertyIndex >= blockList.getBlocks()[sectionIndex].getSection(sectionIndex).getDeclarations().getSize()) {
		return;
	}

	blockList.getBlocks()[sectionIndex].getSection(sectionIndex).removeProperty(propertyName);

	// if the section is empty, remove it
	if (blockList.getBlocks()[sectionIndex].getSection(sectionIndex).getDeclarations().getSize() == 0 or
		blockList.getBlocks()[sectionIndex].getSection(sectionIndex).getSelectors().getSize() == 0 or
		blockList.getBlocks()[sectionIndex].getSection(sectionIndex).getSectionName() == "") {
		blockList.getBlocks()[sectionIndex].getSection(sectionIndex).removeProperty(propertyName);
	}

	std::cout << commandName << " == " << "deleted\n";
}


List<Section> CSS::getSections() const {
	return sections;
}


int CSS::getSectionsCount() {
	return sections.getSize();

	// return sections counter from block list
	//return blockList.getSectionsCount();
}


BlockList<SECTIONS_PER_BLOCK> CSS::getBlockList() const {
	return blockList;
}

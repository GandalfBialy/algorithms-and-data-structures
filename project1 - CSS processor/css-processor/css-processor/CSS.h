#pragma once


#include "Section.h"
#include "BlockList.h"


int const SECTIONS_PER_BLOCK = 8;


class CSS
{
private:
	List<Section> sections;
	BlockList<SECTIONS_PER_BLOCK> blockList;
	
	Block<SECTIONS_PER_BLOCK>* currentBlock;
	int currentSectionIndex = 0;
	//List<Block<SECTIONS_PER_BLOCK>> blocks;

public:
	CSS();

	void appendSection(Section section);
	void printCSS();

	void removeSection(int sectionIndex, String commandName);
	void removeProperty(int sectionIndex, String propertyName, String commandName);

	List<Section> getSections() const;
	int getSectionsCount();
	
	BlockList<SECTIONS_PER_BLOCK> getBlockList() const;
};


#pragma once


#include "Section.h"


class CSS
{
private:
	List<Section> sections;

public:
	CSS();

	void appendSection(Section section);
	void printCSS();

	void removeSection(int sectionIndex);
	void removeProperty(int sectionIndex, String propertyName);

	void setSections(List<Section> sections);
	
	List<Section> getSections();
	int getSectionsCount();
};


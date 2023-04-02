#pragma once


#include "Section.h"


class CSS
{
private:
	List<Section> sections;

public:
	void appendSection(Section section);
	void printSections();

	void setSections(List<Section> sections);
	List<Section> getSections();
};


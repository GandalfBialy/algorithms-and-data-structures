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

	void removeSection(int sectionIndex, String commandName);
	void removeProperty(int sectionIndex, String propertyName, String commandName);

	List<Section> getSections() const;
	int getSectionsCount();
};


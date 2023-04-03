#pragma once


#include "List.h"
#include "Node.h"
#include "String.h"
#include "CSS.h"


int const BUFFER_SIZE = 1000;


class Parser
{
private:
	CSS css;

	Section currentSection;
	Declaration currentDeclaration;

	String inputString;
	//String cssBuffer;
	String cssString;
	String sectionBodyString;
	
	//int bufferIndex;
	int inputStringIndex;
	int sectionBodyBufferIndex;

public:
	Parser();

	//void loadInput();
	void loadCSS();
	
	//void parseInput();
	void parseCSS();
	void parseSection();
	void parseSelectors();
	void parseDeclarations();
	void parseProperties();
	void parseValue();

	bool isWhiteSpace(char character);
};

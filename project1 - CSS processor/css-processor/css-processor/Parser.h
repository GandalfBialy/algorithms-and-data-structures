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
	String cssBuffer;
	int bufferIndex;
	int declarationBufferIndex;

public:
	Parser();

	void loadCSS();
	void parseCSS();
	void parseSection();
	void parseSelectors(Section section);
	void parseDeclarations();
	void parseProperties(String section);
	//void parseProperty(String section);
	void parseValue(String section);
};

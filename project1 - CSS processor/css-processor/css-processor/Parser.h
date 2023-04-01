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

public:
	Parser();

	void loadCSS();
	void parseCSS();
	void parseSection();
	void parseSelectors(String section);
	void parseProperty();
	void parseValue();
};

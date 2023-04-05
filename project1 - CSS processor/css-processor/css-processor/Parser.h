#pragma once


#include "List.h"
#include "Node.h"
#include "String.h"
#include "CSS.h"
#include "CommandsInterpreter.h"


int const BUFFER_SIZE = 32000;


class Parser
{
private:
	CSS* css;
	CommandsInterpreter commandsInterpreter;

	Section currentSection;
	Declaration currentDeclaration;

	String inputString;
	String sectionBodyString;
	
	int inputStringIndex;
	int sectionBodyBufferIndex;

	bool isCSSParserModeOn;

public:
	Parser();
	Parser(const Parser& other);

	void loadInput();
	
	void parseInput();
	//void parseCSS();
	void parseSection();
	void parseSelectors();
	void parseDeclarations();
	void parseProperties();
	void parseValue();
	void parseCommand();

	void executeCommands();
	bool shouldSwitchToCSSParserMode();

	static bool isWhiteSpace(char character);

	void printParsedAndStructuredInput();

	// implement operator= method below
	Parser& operator=(const Parser& other);
};

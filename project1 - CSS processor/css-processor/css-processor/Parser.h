#pragma once


#include "List.h"
#include "Node.h"
#include "String.h"
#include "CSS.h"
#include "CommandsInterpreter.h"


int const BUFFER_SIZE = 8000;
int const BIG_BUFFER_SIZE = 512000;


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
	int nextCommandIndex;

	bool isCSSParserModeOn;

public:
	Parser();
	Parser(const Parser& other);

	void loadInput();
	
	void parseInput();
	void parseSection();
	void parseSelectors();
	void parseDeclarations();
	void parseProperties();
	void parseValue();
	void parseCommand();

	void executeCommands();
	bool shouldSwitchToCSSParserMode();
	void skipCommandsSectionStartSigns();

	static bool isWhiteSpace(char character);

	void printParsedAndStructuredInput();

	Parser& operator=(const Parser& other);
};

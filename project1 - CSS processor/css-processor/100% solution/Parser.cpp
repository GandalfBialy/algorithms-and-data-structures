#include "Parser.h"


Parser::Parser() :
	css{ new CSS },
	commandsInterpreter { CommandsInterpreter(css) },
	currentSection{ Section() },
	currentDeclaration{ Declaration() },
	inputString{ "" },
	sectionBodyString{ "" },
	inputStringIndex{ 0 },
	sectionBodyBufferIndex{ 0 },
	nextCommandIndex{ 0 },
	isCSSParserModeOn{ true }
	 {
}


Parser::Parser(const Parser& other) :
	css{ other.css },
	commandsInterpreter{ other.commandsInterpreter },
	currentSection{ other.currentSection },
	currentDeclaration{ other.currentDeclaration },
	inputString{ other.inputString },
	sectionBodyString{ other.sectionBodyString },
	inputStringIndex{ other.inputStringIndex },
	sectionBodyBufferIndex{ other.sectionBodyBufferIndex },
	isCSSParserModeOn{ other.isCSSParserModeOn },
	nextCommandIndex{ other.nextCommandIndex } {
}


void Parser::loadInput() {
	inputStringIndex = 0;
	char* inputBuffer = new char[BIG_BUFFER_SIZE];
	
	while (inputBuffer[inputStringIndex] = (char)(getchar())) {
		if (inputStringIndex + 2 == BIG_BUFFER_SIZE) {
			inputBuffer[inputStringIndex + 1] = '\0';
			inputString += inputBuffer;
			inputStringIndex = 0;
			continue;
		}

		if (inputBuffer[inputStringIndex] == EOF) {
			inputBuffer[inputStringIndex] = '\0';
			break;
		}

		inputStringIndex++;
	}


	inputString += inputBuffer;
	inputString.trimWhitespace();

	inputStringIndex = 0;

	delete[] inputBuffer;
}


void Parser::parseInput() {
	inputStringIndex = 0;

	while (inputString[inputStringIndex] != '\0') {
		if (isCSSParserModeOn) {
			parseSection();
		}
		else if (shouldSwitchToCSSParserMode()) {
				//commandsInterpreter.printCommands();
				executeCommands();
				
				continue;
		}
		else {
			parseCommand();
		}

		inputStringIndex++;
	}

	//printParsedAndStructuredInput();
}


void Parser::parseSection() {
	String sectionString = "";

	int sectionNameStartIndex = inputStringIndex;
	int sectionNameEndIndex = inputString.findCharacter('{', inputStringIndex) - 1;
	
	sectionString = inputString.substring(sectionNameStartIndex, sectionNameEndIndex);

	sectionString.trimWhitespace();

	this->currentSection = Section(sectionString);

	parseSelectors();
	parseDeclarations();
	
	css->appendSection(currentSection);

	int nextSectionIndex = inputString.findCharacter('{', inputStringIndex);

	//if (nextCommandIndex - nextSectionIndex <= 1000) {
	if (nextCommandIndex - nextSectionIndex <= 0) {
		nextCommandIndex = inputString.findSubstring("????", inputStringIndex);
	}
	
	if (nextCommandIndex < nextSectionIndex and nextSectionIndex != -1 or nextSectionIndex == -1) {
		isCSSParserModeOn = false;
		inputStringIndex = nextCommandIndex;
		skipCommandsSectionStartSigns();
	}
}


void Parser::parseSelectors() {
	String sectionName = currentSection.getSectionName();
	int sectionNameLength = sectionName.getLength();
	
	List<String> selectors;
	String selector = "";
	
	int selectorStartIndex = 0;
	int selectorEndIndex = 0;

	for (int sectionNameIndex = 0; sectionNameIndex < sectionNameLength; sectionNameIndex++) {
		char currentCharacter = sectionName[sectionNameIndex];

		if (currentCharacter == ',') {
			selectorEndIndex = sectionNameIndex - 1;

			selector = sectionName.substring(selectorStartIndex, selectorEndIndex);
			selector.trimWhitespace();
			selectors.append(selector);

			selectorStartIndex = sectionNameIndex + 1;

			continue;
		}
	}

	
	selectorEndIndex = sectionNameLength - 1;

	selector = sectionName.substring(selectorStartIndex, selectorEndIndex);
	selector.trimWhitespace();

	if (selectors.getSize() == 0 and selector == "") {
		currentSection.setHasNoSelectors(true);
		
		selectors.append(selector);
		currentSection.setSelectors(selectors);
	}
	else {
		selectors.append(selector);

		currentSection.setSelectors(selectors);

		//selectors.print();
	}
}


void Parser::parseDeclarations() {
	this->sectionBodyString = "";
	
	int sectionBodyStartIndex = inputString.findCharacter('{', inputStringIndex) + 1;
	int sectionBodyEndIndex = inputString.findCharacter('}', inputStringIndex) - 1;
	
	inputStringIndex = sectionBodyEndIndex + 1;
	
	sectionBodyString = inputString.substring(sectionBodyStartIndex, sectionBodyEndIndex);

	sectionBodyString.trimWhitespace();

	parseProperties();
}


void Parser::parseProperties() {
	String property = "";

	int sectionBodyLength = sectionBodyString.getLength();
	sectionBodyBufferIndex = 0;

	while (sectionBodyBufferIndex < sectionBodyLength) {
		int propertyStartIndex = sectionBodyBufferIndex;
		int propertyEndIndex = sectionBodyString.findCharacter(':', sectionBodyBufferIndex) - 1;

		property = sectionBodyString.substring(propertyStartIndex, propertyEndIndex);

		sectionBodyBufferIndex = propertyEndIndex + 2;

		property.trimWhitespace();


		int propertyIndexIfAlreadyDefined = currentSection.findProperty(property);

		if (propertyIndexIfAlreadyDefined == -1) {
			currentDeclaration.setProperty(property);

			parseValue();

			currentSection.appendDeclaration(currentDeclaration);
		}
		else {
			parseValue();

			String valueName = currentDeclaration.getValue();

			currentSection.replaceDeclarationValue(propertyIndexIfAlreadyDefined, valueName);
		}
		
		sectionBodyBufferIndex++;
	}
}


void Parser::parseValue() {
	String value = "";
	
	int valueStartIndex = sectionBodyBufferIndex;
	int valueEndIndex = sectionBodyString.findCharacter(';', sectionBodyBufferIndex) - 1;

	value = sectionBodyString.substring(valueStartIndex, valueEndIndex);

	sectionBodyBufferIndex = valueEndIndex + 1;

	value.trimWhitespace();

	currentDeclaration.setValue(value);
}


void Parser::parseCommand() {
	String command = "";
	char* commandBuffer = new char[BUFFER_SIZE];
	int commandBufferIndex = 0;

	int inputStringLength = inputString.getLength();

	while (inputStringIndex < inputStringLength) {
		char currentCharacter = inputString[inputStringIndex];

		if (currentCharacter == '\n') {
			commandBuffer[commandBufferIndex] = '\0';
			command = commandBuffer;
			commandBufferIndex = 0;

			command.trimWhitespace();

			if (command.getLength() == 0) {
				delete[] commandBuffer;
				
				return;
			}

			commandsInterpreter.appendCommand(command);

			delete[] commandBuffer;

			return;
		}

		commandBuffer[commandBufferIndex] = currentCharacter;
		commandBufferIndex++;

		inputStringIndex++;
	}

	inputStringIndex++;

	if (commandBufferIndex == 0) {
		delete[] commandBuffer;
		
		return;
	}
	
	commandBuffer[commandBufferIndex] = '\0';
	command = commandBuffer;
	commandBufferIndex = 0;

	command.trimWhitespace();

	std::cerr << "Command: " << std::endl;
	std::cerr << command << std::endl << std::endl;

	commandsInterpreter.appendCommand(command);

	delete[] commandBuffer;
}


void Parser::executeCommands() {
	commandsInterpreter.executeCommands();

	nextCommandIndex = inputString.findSubstring("????", inputStringIndex);

	skipCommandsSectionStartSigns();
}


bool Parser::shouldSwitchToCSSParserMode() {
	int nextCSSBlockIndex = inputString.findSubstring("****", inputStringIndex);

	if (nextCSSBlockIndex - inputStringIndex == 0) {
		isCSSParserModeOn = true;
		return true;
	}

	return false;
}


void Parser::skipCommandsSectionStartSigns() {
	inputStringIndex += 4; // skip "????"
}


 bool Parser::isWhiteSpace(char character) {
	return character == ' ' or character == '\t' or character == '\n' or character == '\r';
}


void Parser::printParsedAndStructuredInput() {
	std::cerr << std::endl << std::endl;
	css->printCSS();

	std::cerr << std::endl << std::endl;
	commandsInterpreter.printCommands();
}


Parser& Parser::operator=(const Parser& other) {
	if (this != &other) {
		inputString = other.inputString;
		inputStringIndex = other.inputStringIndex;
		sectionBodyString = other.sectionBodyString;
		sectionBodyBufferIndex = other.sectionBodyBufferIndex;
		currentSection = other.currentSection;
		currentDeclaration = other.currentDeclaration;
		isCSSParserModeOn = other.isCSSParserModeOn;
		css = other.css;
		commandsInterpreter = other.commandsInterpreter;
	}

	return *this;
}

#include "Parser.h"


Parser::Parser() : inputString(""), sectionBodyString(""), inputStringIndex(0), sectionBodyBufferIndex(0), isCSSParserModeOn(true) {
	css = new CSS();
	commandsInterpreter = CommandsInterpreter(css);

	currentSection = Section();
	currentDeclaration = Declaration();
}


Parser::Parser(const Parser& other) {
	css = other.css;
	commandsInterpreter = other.commandsInterpreter;

	currentSection = other.currentSection;
	currentDeclaration = other.currentDeclaration;

	inputString = other.inputString;
	sectionBodyString = other.sectionBodyString;

	inputStringIndex = other.inputStringIndex;
	sectionBodyBufferIndex = other.sectionBodyBufferIndex;

	isCSSParserModeOn = other.isCSSParserModeOn;
}


void Parser::loadInput() {
	inputStringIndex = 0;
	char* inputBuffer = new char[BUFFER_SIZE];
	
	while (inputBuffer[inputStringIndex] = (char)(getchar())) {
		if (inputStringIndex == BUFFER_SIZE) {
			inputString += inputBuffer;
			inputStringIndex = 0;
			continue;
		}
		else if (inputBuffer[inputStringIndex] == EOF) {
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
		else {
			if (shouldSwitchToCSSParserMode()) {
				commandsInterpreter.printCommands();
				executeCommands();
				
				continue;
			}
			
			parseCommand();
		}

		inputStringIndex++;
	}

	printParsedAndStructuredInput();
}


void Parser::parseSection() {
	//std::cerr << "Parsing section..." << std::endl;
	
	String sectionString = "";
	char* sectionBuffer = new char[BUFFER_SIZE];
	int sectionBufferIndex = 0;

	while (inputString[inputStringIndex] != '{') {
		sectionBuffer[sectionBufferIndex] = inputString[inputStringIndex];
		inputStringIndex++;
		sectionBufferIndex++;
	}

	sectionBuffer[sectionBufferIndex] = '\0';

	sectionString = sectionBuffer;

	sectionString.trimWhitespace();

	this->currentSection = Section(sectionString);

	std::cerr << "Section: " << std::endl;
	std::cerr << sectionString << std::endl << std::endl;

	delete[] sectionBuffer;

	parseSelectors();
	parseDeclarations();
	
	css->appendSection(currentSection);

	int nextSectionIndex = inputString.findCharacter('{', inputStringIndex);

	int nextCommandIndex = inputString.findSubstring("????", inputStringIndex);

	if (nextCommandIndex < nextSectionIndex or nextSectionIndex == -1) {
		isCSSParserModeOn = false;

		inputStringIndex = nextCommandIndex;

		skipCommandsSectionStartSigns();
	}
}


void Parser::parseSelectors() {
	//std::cerr << "Parsing selectors..." << std::endl;
	
	String sectionName = currentSection.getSectionName();
	int sectionNameLength = sectionName.getLength();
	
	List<String> selectors;
	String selector = "";
	char* selectorBuffer = new char[BUFFER_SIZE];
	int selectorBufferIndex = 0;

	for (int sectionNameIndex = 0; sectionNameIndex < sectionNameLength; sectionNameIndex++) {
		char currentCharacter = sectionName[sectionNameIndex];
		
		if (currentCharacter == ',') {
			selectorBuffer[selectorBufferIndex] = '\0';
			selectorBufferIndex = 0;

			selector = selectorBuffer;
			selector.trimWhitespace();
			selectors.append(selector);
			
			continue;
		}
		
		selectorBuffer[selectorBufferIndex] = currentCharacter;
		selectorBufferIndex++;
	}

	selectorBuffer[selectorBufferIndex] = '\0';
	selector = selectorBuffer;

	selector.trimWhitespace();
	selectors.append(selector);

	currentSection.setSelectors(selectors);

	//std::cerr << "Selectors: " << std::endl;
	selectors.print();
	//std::cerr << std::endl;

	delete[] selectorBuffer;
}


void Parser::parseDeclarations() {
	//std::cerr << "Parsing declarations (section body)..." << std::endl;
	
	char* sectionBodyBuffer = new char[BUFFER_SIZE];
	int sectionBodyBufferIndex = 0;

	// skip '{'
	while (inputString[inputStringIndex] != '{') {
		inputStringIndex++;
	}
	inputStringIndex++;

	while (inputString[inputStringIndex] != '}') {
		sectionBodyBuffer[sectionBodyBufferIndex] = inputString[inputStringIndex];
		inputStringIndex++;
		sectionBodyBufferIndex++;
	}

	sectionBodyBuffer[sectionBodyBufferIndex] = '\0';
	sectionBodyString = sectionBodyBuffer;

	//std::cerr << "Section body: " << std::endl;
	//std::cerr << sectionBodyString << std::endl << std::endl;

	sectionBodyString.trimWhitespace();

	//std::cerr << "Section body (trimmed whitespace): " << std::endl;
	//std::cerr << sectionBodyString << std::endl << std::endl;

	parseProperties();

	delete[] sectionBodyBuffer;
}


void Parser::parseProperties() {
	//std::cerr << "Parsing properties..." << std::endl;

	String property = "";
	char* propertyBuffer = new char[BUFFER_SIZE];
	int propertyBufferIndex = 0;

	int sectionBodyLength = sectionBodyString.getLength();
	sectionBodyBufferIndex = 0;

	while (sectionBodyBufferIndex < sectionBodyLength) {
		char currentCharacter = sectionBodyString[sectionBodyBufferIndex];
		
		if (currentCharacter == ':') {
			this->currentDeclaration = Declaration();
			
			propertyBuffer[propertyBufferIndex] = '\0';
			property = propertyBuffer;

			propertyBufferIndex = 0;
			sectionBodyBufferIndex++;

			property.trimWhitespace();

			//std::cerr << "Property: " << std::endl;
			//std::cerr << property << std::endl << std::endl;

			// check if property is already defined
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

			continue;
		}

		propertyBuffer[propertyBufferIndex] = currentCharacter;
		propertyBufferIndex++;

		sectionBodyBufferIndex++;
	}

	delete[] propertyBuffer;
}


void Parser::parseValue() {
	//std::cerr << "Parsing value..." << std::endl;
	
	String value = "";
	char* valueBuffer = new char[BUFFER_SIZE];
	int valueBufferIndex = 0;

	int sectionBodyLength = sectionBodyString.getLength();

	while (sectionBodyBufferIndex < sectionBodyLength) {
		char currentCharacter = sectionBodyString[sectionBodyBufferIndex];
		
		if (currentCharacter == ';') {
			valueBuffer[valueBufferIndex] = '\0';
			value = valueBuffer;
			break;
		}

		valueBuffer[valueBufferIndex] = currentCharacter;
		valueBufferIndex++;
		
		sectionBodyBufferIndex++;
	}

	value.trimWhitespace();

	//std::cerr << "Value: " << std::endl;
	//std::cerr << value << std::endl << std::endl;

	currentDeclaration.setValue(value);

	delete[] valueBuffer;
}


void Parser::parseCommand() {
	//std::cerr << "Parsing command..." << std::endl;

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
				return;
			}

			//std::cerr << "Command: " << std::endl;
			//std::cerr << command << std::endl << std::endl;

			commandsInterpreter.appendCommand(command);

			return;
		}

		commandBuffer[commandBufferIndex] = currentCharacter;
		commandBufferIndex++;

		inputStringIndex++;
	}

	if (commandBufferIndex == 0) {
		return;
	}
	
	commandBuffer[commandBufferIndex] = '\0';
	command = commandBuffer;
	commandBufferIndex = 0;

	command.trimWhitespace();

	//std::cerr << "Command: " << std::endl;
	//std::cerr << command << std::endl << std::endl;

	commandsInterpreter.appendCommand(command);

	delete[] commandBuffer;
}


void Parser::executeCommands() {
	commandsInterpreter.executeCommands();

	inputStringIndex += 4; // skip "????"
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

#include "Parser.h"


Parser::Parser() {
	currentDeclaration = Declaration();

	inputString = "";
	cssString = "";

	inputStringIndex = 0;
	sectionBodyBufferIndex = 0;
}


// TODO: handle input greater than BUFFER_SIZE
void Parser::loadCSS() {
	inputStringIndex = 0;
	char* inputBuffer = new char[BUFFER_SIZE];
	String line = "";
	
	while (inputBuffer[inputStringIndex] = getchar()) {
		if (inputStringIndex == BUFFER_SIZE) {
			line += inputBuffer;
			inputStringIndex = 0;
			continue;
		}
		else if (inputBuffer[inputStringIndex] == EOF) {
			inputBuffer[inputStringIndex] = '\0';
			break;
		}

		inputStringIndex++;
	}

	line += inputBuffer;
	//std::cerr << line;

	//cssString = line;
	cssString = line;

	delete[] inputBuffer;
}


void Parser::parseCSS() {
	inputStringIndex = 0;

	while (cssString[inputStringIndex] != '\0' and cssString[inputStringIndex + 1] != '\0') {
		parseSection();

		inputStringIndex++;

		// TODO: commands/instructions also should be parsed here, a flag should do the work
	}

	std::cerr << std::endl << std::endl;
	css.printCSS();
}


void Parser::parseSection() {
	std::cerr << "Parsing section..." << std::endl;
	
	String sectionString = "";
	char* sectionBuffer = new char[BUFFER_SIZE];
	int sectionBufferIndex = 0;

	while (cssString[inputStringIndex] != '{') {
		sectionBuffer[sectionBufferIndex] = cssString[inputStringIndex];
		inputStringIndex++;
		sectionBufferIndex++;
	}

	sectionBuffer[sectionBufferIndex] = '\0';

	sectionString = sectionBuffer;
	this->currentSection = Section(sectionString);

	std::cerr << "Section: " << std::endl;
	std::cerr << sectionString << std::endl << std::endl;

	delete[] sectionBuffer;

	parseSelectors();
	parseDeclarations();
	
	css.appendSection(currentSection);
}


void Parser::parseSelectors() {
	std::cerr << "Parsing selectors..." << std::endl;
	
	String sectionName = currentSection.getSectionName();
	int sectionNameLength = sectionName.getLength();
	
	List<String> selectors;
	String selector = "";
	char* selectorBuffer = new char[BUFFER_SIZE];
	int selectorBufferIndex = 0;

	for (int i = 0; i < sectionNameLength; i++) {
		if (sectionName[i] == ',') {
			selectorBuffer[selectorBufferIndex] = '\0';
			selector = selectorBuffer;
			selectors.append(selector);
			selectorBufferIndex = 0;
			continue;
		}
		else if (sectionName[i] == ' ') {
			continue;
		}

		selectorBuffer[selectorBufferIndex] = sectionName[i];
		selectorBufferIndex++;
	}

	selectorBuffer[selectorBufferIndex] = '\0';
	selector = selectorBuffer;
	selectors.append(selector);

	currentSection.setSelectors(selectors);
	//css.appendSection(currentSection);

	std::cerr << "Selectors: " << std::endl;
	selectors.print();
	std::cerr << std::endl;

	delete[] selectorBuffer;
}


void Parser::parseDeclarations() {
	std::cerr << "Parsing declarations (section body)..." << std::endl;
	
	char* sectionBodyBuffer = new char[BUFFER_SIZE];
	int sectionBodyBufferIndex = 0;

	// skip '{'
	while (cssString[inputStringIndex] != '{') {
		inputStringIndex++;
	}
	inputStringIndex++;

	while (cssString[inputStringIndex] != '}') {
		sectionBodyBuffer[sectionBodyBufferIndex] = cssString[inputStringIndex];
		inputStringIndex++;
		sectionBodyBufferIndex++;
	}

	sectionBodyBuffer[sectionBodyBufferIndex] = '\0';
	sectionBodyString = sectionBodyBuffer;

	std::cerr << "Section body: " << std::endl;
	std::cerr << sectionBodyString << std::endl << std::endl;

	sectionBodyString.trimWhitespace();

	std::cerr << "Section body (trimmed whitespace): " << std::endl;
	std::cerr << sectionBodyString << std::endl << std::endl;

	parseProperties();

	delete[] sectionBodyBuffer;
}


void Parser::parseProperties() {
	std::cerr << "Parsing properties..." << std::endl;

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

			std::cerr << "Property: " << std::endl;
			std::cerr << property << std::endl << std::endl;

			currentDeclaration.setProperty(property);

			parseValue();

			currentSection.appendDeclaration(currentDeclaration);

			sectionBodyBufferIndex++;

			continue;
		}

		//if (!isWhiteSpace(currentCharacter)) {
			propertyBuffer[propertyBufferIndex] = currentCharacter;
			propertyBufferIndex++;
		//}

		sectionBodyBufferIndex++;
	}

	delete[] propertyBuffer;
}


void Parser::parseValue() {
	std::cerr << "Parsing value..." << std::endl;
	
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

		//if (!isWhiteSpace(currentCharacter)) {
			valueBuffer[valueBufferIndex] = currentCharacter;
			valueBufferIndex++;
		//}
		
		sectionBodyBufferIndex++;
	}

	value.trimWhitespace();

	std::cerr << "Value: " << std::endl;
	std::cerr << value << std::endl << std::endl;

	currentDeclaration.setValue(value);

	delete[] valueBuffer;
}


bool Parser::isWhiteSpace(char character) {
	return character == ' ' or character == '\t' or character == '\n' or character == '\r';
}

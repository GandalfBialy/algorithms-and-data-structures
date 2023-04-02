#include "Parser.h"


Parser::Parser() {
	bufferIndex = 0;
	declarationBufferIndex = 0;
}


void Parser::loadCSS() {
	bufferIndex = 0;
	char* buffer = new char[BUFFER_SIZE];
	String line = "";
	
	while (buffer[bufferIndex] = getchar()) {
		if (bufferIndex == BUFFER_SIZE) {
			line += buffer;
			bufferIndex = 0;
			continue;
		}
		else if (buffer[bufferIndex] == EOF) {
			buffer[bufferIndex] = '\0';
			break;
		}

		bufferIndex++;
	}

	line += buffer;
	//std::cerr << line;

	cssBuffer = line;

	delete[] buffer;
}


void Parser::parseCSS() {
	bufferIndex = 0;

	while (cssBuffer[bufferIndex] != '\0' and cssBuffer[bufferIndex + 1] != '\0') {
		parseSection();

		bufferIndex++;


		// TODO: commands/instructions also should be parsed here, a flag should do the work

		/*if (cssBuffer[bufferIndex] == '{') {
			parseProperty();
		}*/

	}

	std::cerr << "Sections:" << std::endl;
	css.printSections();
}


void Parser::parseSection() {
	std::cerr << "Parsing section..." << std::endl;
	
	String sectionString = "";
	char* sectionBuffer = new char[BUFFER_SIZE];
	int sectionBufferIndex = 0;

	while (cssBuffer[bufferIndex] != '{') {
		sectionBuffer[sectionBufferIndex] = cssBuffer[bufferIndex];
		bufferIndex++;
		sectionBufferIndex++;
	}

	sectionBuffer[sectionBufferIndex] = '\0';

	sectionString = sectionBuffer;
	Section section(sectionString);

	std::cerr << "Section: " << std::endl;
	std::cerr << sectionString << std::endl << std::endl;

	delete[] sectionBuffer;

	parseSelectors(section);
	parseDeclarations();
}


void Parser::parseSelectors(Section section) {
	std::cerr << "Parsing selectors..." << std::endl;
	
	String sectionName = section.getSectionName();
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

	section.setSelectors(selectors);
	css.appendSection(section);

	std::cerr << "Selectors: " << std::endl;
	selectors.print();
	std::cerr << std::endl;
}


void Parser::parseDeclarations() {
	std::cerr << "Parsing declarations..." << std::endl;
	
	String declaration = "";
	char* declarationBuffer = new char[BUFFER_SIZE];
	int declarationBufferIndex = 0;

	while (cssBuffer[bufferIndex] != '}') {
		declarationBuffer[declarationBufferIndex] = cssBuffer[bufferIndex];
		bufferIndex++;
		declarationBufferIndex++;
	}

	declarationBuffer[declarationBufferIndex] = '}';
	declarationBufferIndex++;

	declarationBuffer[declarationBufferIndex] = '\0';
	declaration = declarationBuffer;

	std::cerr << "Declaration: " << std::endl;
	std::cerr << declaration << std::endl << std::endl;

	parseProperties(declaration);

	delete[] declarationBuffer;
}


void Parser::parseProperties(String declaration) {
	std::cerr << "Parsing properties..." << std::endl;
	
	String property = "";
	char* propertyBuffer = new char[BUFFER_SIZE];
	int propertyBufferIndex = 0;

	for (int i = 0; i < declaration.getLength(); i++) {
		if (declaration[i] == ':') {
			propertyBuffer[propertyBufferIndex] = '\0';
			property = propertyBuffer;
			break;
		}

		propertyBuffer[propertyBufferIndex] = declaration[i];
		propertyBufferIndex++;

		parseValue(declaration, propertyBufferIndex + 1);
	}

	std::cerr << "Property: " << std::endl;
	std::cerr << property << std::endl << std::endl;

	parseValue(declaration, propertyBufferIndex + 1);
}


//void Parser::parseProperty(String declaration) {
//	std::cerr << "Parsing property..." << std::endl;
//	
//	String property = "";
//	char* propertyBuffer = new char[BUFFER_SIZE];
//	int propertyBufferIndex = 0;
//
//	for (int i = 0; i < declaration.getLength(); i++) {
//		if (declaration[i] == ':') {
//			propertyBuffer[propertyBufferIndex] = '\0';
//			property = propertyBuffer;
//			break;
//		}
//
//		propertyBuffer[propertyBufferIndex] = declaration[i];
//		propertyBufferIndex++;
//	}
//
//	std::cerr << "Property: " << std::endl;
//	std::cerr << property << std::endl << std::endl;
//
//	parseValue(declaration, propertyBufferIndex);
//}


void Parser::parseValue(String declaration) {
	std::cerr << "Parsing value..." << std::endl;
	
	String value = "";
	char* valueBuffer = new char[BUFFER_SIZE];
	int valueBufferIndex = currentBufferIndex;

	for (int i = currentBufferIndex; i < declaration.getLength(); i++) {
		if (declaration[i] == ';') {
			valueBuffer[valueBufferIndex] = '\0';
			value = valueBuffer;
			break;
		}

		valueBuffer[valueBufferIndex] = declaration[i];
		valueBufferIndex++;
	}
	std::cerr << "Value: " << std::endl;
	std::cerr << value << std::endl << std::endl;
}

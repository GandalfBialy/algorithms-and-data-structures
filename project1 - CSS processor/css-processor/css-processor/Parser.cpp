#include "Parser.h"


Parser::Parser() {
	bufferIndex = 0;
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
	std::cout << line;

	cssBuffer = line;

	delete[] buffer;
}


void Parser::parseCSS() {
	bufferIndex = 0;

	parseSection();

	//while (cssBuffer[bufferIndex] != '\0') {
		//parseSection();
		// 
		// TODO: commands/instructions also should be parsed here, a flag should do the work

		/*if (cssBuffer[bufferIndex] == '{') {
			parseProperty();
		}*/
	//}
}


void Parser::parseSection() {
	std::cout << "Parsing section..." << std::endl;
	
	String section = "";
	char* sectionBuffer = new char[BUFFER_SIZE];
	int sectionBufferIndex = 0;

	while (cssBuffer[bufferIndex] != '{') {
		sectionBuffer[sectionBufferIndex] = cssBuffer[bufferIndex];
		bufferIndex++;
		sectionBufferIndex++;
	}

	sectionBuffer[sectionBufferIndex] = '\0';

	section = sectionBuffer;

	std::cout << section;

	delete[] sectionBuffer;

	parseSelectors(section);
	parseDeclarations();
}


void Parser::parseSelectors(String section) {
	List<String> selectors;
	String selector = "";
	char* selectorBuffer = new char[BUFFER_SIZE];
	int selectorBufferIndex = 0;

	for (int i = 0; i < section.getLength(); i++) {
		if (section[i] == ',') {
			selectorBuffer[selectorBufferIndex] = '\0';
			selectors.append(selector);
			selectorBufferIndex = 0;
			continue;
		}

		selectorBuffer[selectorBufferIndex] = section[i];
		selectorBufferIndex++;
	}

	selectorBuffer[selectorBufferIndex] = '\0';
	selectors.append(selector);

	std::cout << "Selectors: " << std::endl;
	selectors.print();
}


void Parser::parseDeclarations() {

}


void Parser::parseProperty(String declaration) {

}


void Parser::parseValue(String declaration) {


}

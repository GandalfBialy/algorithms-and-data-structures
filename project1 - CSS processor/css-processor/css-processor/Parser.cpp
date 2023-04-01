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

	while (cssBuffer[bufferIndex] != '\0') {
		//parseSelector();

		if (cssBuffer[bufferIndex] == '{') {
			parseProperty();
		}
	}
}


void Parser::parseSection() {
	String section = "";
	char* sectionBuffer = new char[BUFFER_SIZE];
	int sectionBufferIndex = 0;

	while (cssBuffer[bufferIndex] != '{') {
		sectionBuffer[sectionBufferIndex] = cssBuffer[bufferIndex];
		bufferIndex++;
	}

	sectionBuffer[sectionBufferIndex] = '\0';

	section = sectionBuffer;

	std::cout << section;

	parseSelectors(section);

	delete[] sectionBuffer;
}


void Parser::parseSelectors(String section) {
	/*List<String> selectors;
	String selector = "";
	int selectorIndex = 0;
	for (int i = 0; i < section.getLength(); i++) {
		if (section[i] == ',') {
			selector[selectorIndex] = '\0';
			selectors.pushBack(selector);
			selectorIndex = 0;
			continue;
		}
		selector[selectorIndex] = section[i];
		selectorIndex++;
	}
	selector[selectorIndex] = '\0';
	selectors.pushBack(selector);
	for (int i = 0; i < selectors.getSize(); i++) {
		std::cout << selectors[i] << std::endl;
	}*/
}

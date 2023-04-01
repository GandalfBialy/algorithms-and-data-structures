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
}


void Parser::parseCSS() {
	bufferIndex = 0;

	while (cssBuffer[bufferIndex] != '\0') {
		parseSelector();

		if (cssBuffer[bufferIndex] == '{') {
			parseProperty();
		}
	}
}


void Parser::parseSection() {
	String selector = "";

	while (cssBuffer[bufferIndex] != '{') {
		//selector += cssBuffer[bufferIndex];
		bufferIndex++;
	}

	// add selector to css


	std::cout << selector;
}

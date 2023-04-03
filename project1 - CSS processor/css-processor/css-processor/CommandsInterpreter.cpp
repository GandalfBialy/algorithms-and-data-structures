#include "CommandsInterpreter.h"


CommandsInterpreter::CommandsInterpreter() {
	commands = List<String>();
}


void CommandsInterpreter::appendCommand(String command) {
	commands.append(command);
}


int CommandsInterpreter::getSectionsCount(CSS css) {
	return css.getSectionsCount();
}


void CommandsInterpreter::printCommands() {
	std::cerr << "--- PRINTING COMMANDS ---" << std::endl;
	
	for (int i = 0; i < commands.getSize(); i++) {
		std::cerr << commands[i] << std::endl;
	}
}


int CommandsInterpreter::getSelectorsCount(CSS css, int sectionIndex) {
	return css.getSections()[sectionIndex].getSelectors().getSize();
}


int CommandsInterpreter::getDeclarationsCount(CSS css, int sectionIndex, int selectorIndex) {
	return css.getSections()[sectionIndex].getDeclarations().getSize();
}

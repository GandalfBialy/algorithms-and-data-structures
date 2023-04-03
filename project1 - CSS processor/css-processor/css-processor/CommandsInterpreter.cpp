#include "CommandsInterpreter.h"


CommandsInterpreter::CommandsInterpreter() {
	commands = List<String>();
}


void CommandsInterpreter::executeCommands(CSS css) {
	for (int commandIndex = 0; commandIndex < commands.getSize(); commandIndex++) {
		String command = commands[commandIndex];
		int commasCount = command.countCharacter(',');

		std::cout << command << " == ";

		if (commasCount == 0) {
			if (command == "?") {
				std::cout << getSectionsCount(css) << "\n";
			}
		}
	}
}


void CommandsInterpreter::appendCommand(String command) {
	commands.append(command);
}


int CommandsInterpreter::getSectionsCount(CSS css) {
	return css.getSectionsCount();
}


void CommandsInterpreter::printCommands() {
	std::cerr << "--- PRINTING COMMANDS ---" << std::endl;
	
	for (int commandIndex = 0; commandIndex < commands.getSize(); commandIndex++) {
		std::cerr << commandIndex << ".: " << commands[commandIndex] << std::endl;
	}
}


int CommandsInterpreter::getSelectorsCount(CSS css, int sectionIndex) {
	return css.getSections()[sectionIndex].getSelectors().getSize();
}


int CommandsInterpreter::getDeclarationsCount(CSS css, int sectionIndex, int selectorIndex) {
	return css.getSections()[sectionIndex].getDeclarations().getSize();
}

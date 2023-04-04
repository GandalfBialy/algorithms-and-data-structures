#include "CommandsInterpreter.h"


CommandsInterpreter::CommandsInterpreter() {
	commands = List<String>();
}


void CommandsInterpreter::executeCommands(CSS css) {
	std::cerr << "--- EXECUTING COMMANDS ---" << std::endl;

	while(commands.getSize() > 0) {
		String command = commands.front();
		int commasCount = command.countCharacter(',');

		std::cout << command << " == ";

		if (commasCount == 0) {
			if (command == "?") {
				std::cout << getSectionsCount(css);
			}
		}

		std::cout << "\n";

		commands.popFront();
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

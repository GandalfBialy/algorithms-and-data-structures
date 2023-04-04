#include "CommandsInterpreter.h"


CommandsInterpreter::CommandsInterpreter() {
	commands = List<Command>();
	css = nullptr;
}


CommandsInterpreter::CommandsInterpreter(CSS* css) {
	commands = List<Command>();
	this->css = css;
}


Command CommandsInterpreter::parseCommand(String commandString) {
	Command command = Command(commandString);

	return command;
}


void CommandsInterpreter::executeCommands() {
	std::cerr << "--- EXECUTING COMMANDS ---" << std::endl;

	while(commands.getSize() > 0) {
		Command command = commands.front();
		
		executeCommand(command);

		commands.popFront();
	}
}


void CommandsInterpreter::executeCommand(Command command) {
	String commandName = command.getCommandName();
	int commasCount = commandName.countCharacter(',');

	std::cout << commandName << " == ";

	if (commasCount == 0) {
		if (commandName == "?") {
			std::cout << getSectionsCount();
		}
	}
	/*else if (commasCount == 2) {
		if
	}*/

	std::cout << "\n";
}


void CommandsInterpreter::appendCommand(String commandString) {
	Command command = parseCommand(commandString);

	commands.append(command);
}


int CommandsInterpreter::getSectionsCount() {
	return css->getSectionsCount();
}


void CommandsInterpreter::printCommands() {
	std::cerr << "--- PRINTING COMMANDS ---" << std::endl;
	
	for (int commandIndex = 0; commandIndex < commands.getSize(); commandIndex++) {
		String commandName = commands[commandIndex].getCommandName();

		std::cerr << commandIndex << ".: " << commandName << std::endl;
	}
}


int CommandsInterpreter::getSelectorsCount(int sectionIndex) {
	//sectionIndex--;

	return css->getSections()[sectionIndex].getSelectors().getSize();
}


int CommandsInterpreter::getDeclarationsCount(int sectionIndex, int selectorIndex) {
	return css->getSections()[sectionIndex].getDeclarations().getSize();
}


String CommandsInterpreter::getPropertyValue(int sectionIndex, String propertyName) {
	List<Declaration> declarations = css->getSections()[sectionIndex].getDeclarations();

	for (int declarationIndex = 0; declarationIndex < declarations.getSize(); declarationIndex++) {
		if (declarations[declarationIndex].getProperty() == propertyName) {
			return declarations[declarationIndex].getValue();
		}
	}

	return "";
}


void CommandsInterpreter::setCSS(CSS* css) {
	this->css = css;
}
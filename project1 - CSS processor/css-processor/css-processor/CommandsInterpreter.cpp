#include "CommandsInterpreter.h"


CommandsInterpreter::CommandsInterpreter() {
	commands = List<String>();
}


void CommandsInterpreter::appendCommand(String command) {
	commands.append(command);
}


void CommandsInterpreter::printCommands() {
	std::cerr << "--- PRINTING COMMANDS ---" << std::endl;
	
	for (int i = 0; i < commands.getSize(); i++) {
		std::cerr << commands[i] << std::endl;
	}
}

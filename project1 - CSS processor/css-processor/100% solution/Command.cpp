#include "Command.h"


Command::Command() : commandName("") {
	arguments[0] = "";
	arguments[1] = "";
	arguments[2] = "";
}


Command::Command(String commandName) : commandName(commandName) {
	arguments[0] = "";
	arguments[1] = "";
	arguments[2] = "";
}


Command::Command(String commandName, String arguments[3]) :
	commandName(commandName),
	arguments{ arguments[0], arguments[1], arguments[2] } {
}


String Command::getCommandName() const {
	return commandName;
}


String* Command::getArguments() {
	return arguments;
}

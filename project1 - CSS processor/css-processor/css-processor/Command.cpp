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


Command::Command(String commandName, String arguments[3]) : commandName(commandName) {
	this->arguments[0] = arguments[0];
	this->arguments[1] = arguments[1];
	this->arguments[2] = arguments[2];
}


void Command::setCommandName(String commandName) {
	this->commandName = commandName;
}


void Command::setArguments(String arguments[3]) {
	this->arguments[0] = arguments[0];
	this->arguments[1] = arguments[1];
	this->arguments[2] = arguments[2];
}


String Command::getCommandName() const {
	return commandName;
}


String* Command::getArguments() {
	return arguments;
}

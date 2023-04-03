#pragma once


#include "String.h"
#include "List.h"


class CommandsInterpreter
{
private:
	List<String> commands;

public:
	CommandsInterpreter();

	void appendCommand(String command);
	void printCommands();
};


#pragma once


#include "String.h"


class Command
{
private:
	String commandName;
	String arguments[3];

public:
	Command();
	Command(String commandName);

	void setCommandName(String commandName);
	void setArguments(String arguments[3]);

	String getCommandName();
	String* getArguments();
};


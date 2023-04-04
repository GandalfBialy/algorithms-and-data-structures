#include "CommandsInterpreter.h"


CommandsInterpreter::CommandsInterpreter() {
	commands = List<Command>();
	css = nullptr;
}


CommandsInterpreter::CommandsInterpreter(CSS* css) {
	commands = List<Command>();
	this->css = css;
}


void CommandsInterpreter::appendCommand(String commandString) {
	Command command = parseCommand(commandString);

	commands.append(command);
}


Command CommandsInterpreter::parseCommand(String commandName) {
	int commasCount = commandName.countCharacter(',');
	
	if (commasCount == 2) {
		String arguments[3];
		int firstCommaIndex = commandName.findCharacter(',');
		int secondCommaIndex = commandName.findCharacter(',', firstCommaIndex + 1);
		int commandNameLength = commandName.getLength();

		arguments[0] = commandName.substring(0, firstCommaIndex - 1);
		arguments[1] = commandName.substring(firstCommaIndex + 1, secondCommaIndex - 1);
		arguments[2] = commandName.substring(secondCommaIndex + 1, commandNameLength - 1);

		return Command(commandName, arguments);
	}

	return Command(commandName);
}


void CommandsInterpreter::printCommands() {
	std::cerr << "--- PRINTING COMMANDS ---" << std::endl;

	for (int commandIndex = 0; commandIndex < commands.getSize(); commandIndex++) {
		Command command = commands[commandIndex];
		String commandName = command.getCommandName();
		String* arguments = command.getArguments();

		std::cerr << commandIndex << ".: " << commandName << "[" << arguments[0] << ";" << arguments[1] << ";" << arguments[2] << "]" << std::endl;
	}
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
	String* arguments = command.getArguments();

	std::cout << commandName << " == ";

	// ? (command)
	if (commandName[0] == '?') {
		std::cout << getSectionsCount() << "\n";
	}
	// i,S,? OR z,S,? (command)
	else if (arguments[1] == "S" and arguments[2] == "?") {
		// i,S,? (command)
		if (isArgumentNumber(arguments[0])) {
			int sectionIndex = arguments[0].parseToInt() - 1;

			std::cout << getSelectorsCount(sectionIndex) << "\n";

			return;
		}
		
		// z,S,? (command)
		std::cout << getSelectorsCount(arguments[0]) << "\n";
	}
	// i,A,? (command)
	else if (arguments[1] == "A" and arguments[2] == "?") {
		int sectionIndex = arguments[0].parseToInt() - 1;

		std::cout << getDeclarationsCount(sectionIndex) << "\n";
	}
	// i,A,n (command)
	else if (arguments[1] == "A" and arguments[2].getLength() > 1) {
		int sectionIndex = arguments[0].parseToInt() - 1;
		String propertyName = arguments[2];

		std::cout << getPropertyValue(sectionIndex, propertyName) << "\n";
	}
	// i,D,* OR i,D,n (command)
	else if (arguments[1] == "D") {
		// i,D,* (command)
		if (arguments[2] == "*") {
			int sectionIndex = arguments[0].parseToInt() - 1;

			css->removeSection(sectionIndex);
			std::cout << "deleted\n";

			return;
		}

		
		// i, D, n (command)
		// delete attribute from i section and of name n
		//int sectionIndex = arguments[0].parseToInt() - 1;
		//String propertyName = arguments[2];
		//
		//// find property in declaration
		//int declarationIndex = -1;
		//
		//for (int declarationIndex = 0; declarationIndex < css->getSections()[sectionIndex].getDeclarations().getSize(); declarationIndex++) {
		//	if (css->getSections()[sectionIndex].getDeclarations()[declarationIndex].getProperty() == propertyName) {
		//		break;
		//	}
		//}

		//// delete property
		//css->getSections()[sectionIndex].getDeclarations().removeAt(declarationIndex);

		//// print section

		//// if declaration is empty, delete it
		//if (css->getSections()[sectionIndex].getDeclarations().getSize() == 0) {
		//	css->removeSection(sectionIndex);
		//}

		//std::cout << "deleted\n";
	}

	std::cout << "\n";
}


bool CommandsInterpreter::isArgumentNumber(String argument) {
	for (int characterIndex = 0; characterIndex < argument.getLength(); characterIndex++) {
		if (argument[characterIndex] < '0' or argument[characterIndex] > '9') {
			return false;
		}
	}

	return true;
}


void CommandsInterpreter::setCSS(CSS* css) {
	this->css = css;
}


// Commands


int CommandsInterpreter::getSectionsCount() {
	return css->getSectionsCount();
}


int CommandsInterpreter::getSelectorsCount(int sectionIndex) {
	//sectionIndex--;

	return css->getSections()[sectionIndex].getSelectors().getSize();
}


int CommandsInterpreter::getDeclarationsCount(int sectionIndex) {
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


int CommandsInterpreter::getSelectorsCount(String selectorName) {
	int selectorsCount = 0;
	List<Section> sections = css->getSections();

	for (Node<Section>* section = sections.getHead();; section = section->next) {
		List<String> selectors = section->data.getSelectors();

		//std::cerr << "Current section: " << section->data.getSectionName() << "\n";

		for (Node<String>* selector = selectors.getHead();; selector = selector->next) {
			//std::cerr << "Current selector: " << selector->data << "\n";

			if (selector->data == selectorName) {
				selectorsCount++;
			}

			if (selector->next == nullptr) {
				break;
			}
		}

		if (section->next == nullptr) {
			break;
		}
	}

	return selectorsCount;
}

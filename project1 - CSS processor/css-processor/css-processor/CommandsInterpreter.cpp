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
	currentCommandName = command.getCommandName();
	currentArguments = command.getArguments();
	String* arguments = command.getArguments();

	// ? (command)
	handleSectionsCountCommand();

	// i,S,? (command)
	handleSelectorsCountBySectionIndexCommand();

	// z,S,? (command)
	handleSelectorsCountBySelectorNameCommand();

	// i,S,j (command)
	handleSelectorNameByBlockIndexAndSelectorIndexCommand();

	// i,A,? OR n,A,? (command)
	if (arguments[1] == "A" and arguments[2] == "?") {
		// i,A,? (command)
		if (isArgumentNumber(arguments[0])) {
			int sectionIndex = arguments[0].parseToInt() - 1;

			std::cout << getDeclarationsCount(sectionIndex) << "\n";

			return;
		}
	
		// n,A,? (command) - TO IMPLEMENT
		std::cout << "NOT IMPLEMENTED\n";
	}
	// i,A,n (command)
	else if (arguments[1] == "A" and arguments[2].getLength() > 1) {
		int sectionIndex = arguments[0].parseToInt() - 1;
		String propertyName = arguments[2];

		std::cout << getPropertyValue(sectionIndex, propertyName) << "\n";
	}
	// z,E,n (command)
	else if (arguments[1] == "E") {
		std::cout << getPropertyValue(arguments[0], arguments[2]) << "\n";

		//std::cout << "NOT IMPLEMENTED\n";
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
		int sectionIndex = arguments[0].parseToInt() - 1;
		String propertyName = arguments[2];
		
		css->removeProperty(sectionIndex, propertyName);

		std::cout << "deleted\n";
	}
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

// ? (command)
int CommandsInterpreter::getSectionsCount() {
	return css->getSectionsCount();
}


// i,S,? (command)
int CommandsInterpreter::getSelectorsCount(int sectionIndex) {
	Section section = css->getSections()[sectionIndex];

	return section.getSelectors().getSize();
}


// z,S,? (command)
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


// i,S,j (command)
String CommandsInterpreter::getSelectorName(int sectionIndex, int selectorIndex) {
	Section section = css->getSections()[sectionIndex];
	List<String> selectors = section.getSelectors();

	int currentSelectorIndex = 0;
	for (Node<String>* selector = selectors.getHead(); selector != nullptr; selector = selector->next) {
		if (currentSelectorIndex == selectorIndex) {
			return selector->data;
		}

		currentSelectorIndex++;
	}

	return "";
}


// i,A,? (command)
int CommandsInterpreter::getDeclarationsCount(int sectionIndex) {
	Section section = css->getSections()[sectionIndex];
	
	return section.getDeclarations().getSize();
}


// i,A,n (command)
String CommandsInterpreter::getPropertyValue(int sectionIndex, String propertyName) {
	Section section = css->getSections()[sectionIndex];
	List<Declaration> declarations = section.getDeclarations();
	
	for (Node<Declaration>* declaration = declarations.getHead(); declaration != nullptr; declaration = declaration->next) {
		if (declaration->data.getProperty() == propertyName) {
			return declaration->data.getValue();
		}
	}

	return "";
}


// z,E,n (command)
String CommandsInterpreter::getPropertyValue(String selectorName, String propertyName) {
	List<Section> sections = css->getSections();
	
	for (Node<Section>* section = sections.getTail(); section != nullptr; section = section->previous) {
		List<String> selectors = section->data.getSelectors();

		for (Node<String>* selector = selectors.getHead(); selector != nullptr; selector = selector->next) {
			if (selector->data == selectorName) {
				List<Declaration> declarations = section->data.getDeclarations();

				for (Node<Declaration>* declaration = declarations.getHead(); declaration != nullptr; declaration = declaration->next) {
					if (declaration->data.getProperty() == propertyName) {
						return declaration->data.getValue();
					}
				}
			}
		}
	}

	return "";
}


// Commands handling

// ? (command)
void CommandsInterpreter::handleSectionsCountCommand() {
	if (currentCommandName[0] == '?') {
		currentCommandAnswer = getSectionsCount();
		
		std::cout << currentCommandName << " == " << currentCommandAnswer << "\n";
	}
}


// i,S,? (command)
void CommandsInterpreter::handleSelectorsCountBySectionIndexCommand() {
	if (currentArguments[1] == "S" and currentArguments[2] == "?" and isArgumentNumber(currentArguments[0])) {
		int sectionIndex = currentArguments[0].parseToInt() - 1;
		int sectionsCount = getSectionsCount();

		if (sectionIndex < 0 or sectionIndex >= sectionsCount) {
			return;
		}
		
		currentCommandAnswer = getSelectorsCount(sectionIndex);
		
		std::cout << currentCommandName << " == " << currentCommandAnswer << "\n";
	}
}


// z,S,? (command)
void CommandsInterpreter::handleSelectorsCountBySelectorNameCommand() {
	String selectorName = currentArguments[0];
	
	if (currentArguments[1] == "S" and currentArguments[2] == "?" and !isArgumentNumber(selectorName)) {
		//currentCommandAnswer = getSelectorsCount(selectorName);
		currentCommandAnswer = "";

		if (currentCommandAnswer == 0) {
			return;
		}
		
		std::cout << currentCommandName << " == " << currentCommandAnswer << "\n";
	}
}


// i,S,j (command)
void CommandsInterpreter::handleSelectorNameByBlockIndexAndSelectorIndexCommand() {
	if (currentArguments[1] == "S" and isArgumentNumber(currentArguments[0]) and isArgumentNumber(currentArguments[2])) {
		int sectionIndex = currentArguments[0].parseToInt() - 1;
		int selectorIndex = currentArguments[2].parseToInt() - 1;
		int sectionsCount = getSectionsCount();

		if (sectionIndex < 0 or sectionIndex >= sectionsCount) {
			return;
		}

		int selectorsCount = getSelectorsCount(sectionIndex);

		if (selectorIndex < 0 or selectorIndex >= selectorsCount) {
			return;
		}

		currentCommandAnswer = getSelectorName(sectionIndex, selectorIndex);

		std::cout << currentCommandName << " == " << currentCommandAnswer << "\n";
	}
}


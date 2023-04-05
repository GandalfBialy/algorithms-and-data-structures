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

	// ? (command)
	handleSectionsCountCommand();

	// i,S,? (command)
	handleSelectorsCountBySectionIndexCommand();

	// z,S,? (command)
	handleSelectorsCountBySelectorNameCommand();

	// i,S,j (command)
	handleSelectorNameByBlockIndexAndSelectorIndexCommand();

	// i,A,? (command)
	handleDeclarationsCountBySectionIndexCommand();

	// n,A,? (command)
	handlePropertyCountByPropertyNameCommand();

	// i,A,n (command)
	handlePropertyValueBySectionIndexAndPropertyNameCommand();
	
	// z,E,n (command)
	handlePropertyValueBySelectorAndPropertyNameCommand();

	// i,D,* (command)
	handleSectionDeletionCommand();

	// i,D,n (command)
	handlePropertyDeletionCommand();
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


// n,A,? (command)
int CommandsInterpreter::getPropertyCount(String propertyName) {
	int propertyCount = 0;
	List<Section> sections = css->getSections();

	for (Node<Section>* section = sections.getHead();; section = section->next) {
		List<Declaration> declarations = section->data.getDeclarations();

		for (Node<Declaration>* declaration = declarations.getHead();; declaration = declaration->next) {
			if (declaration->data.getProperty() == propertyName) {
				propertyCount++;
			}

			if (declaration->next == nullptr) {
				break;
			}
		}

		if (section->next == nullptr) {
			break;
		}
	}

	return propertyCount;
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
	if (currentArguments[1] == "S" and currentArguments[2] == "?" and currentArguments[0].isNumber()) {
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
	
	//if (currentArguments[1] == "S" and currentArguments[2] == "?" and !isArgumentNumber(selectorName)) {
	if (currentArguments[1] == "S" and currentArguments[2] == "?" and !selectorName.isNumber()) {
		currentCommandAnswer = getSelectorsCount(selectorName);
		if (currentCommandAnswer == "") {
			return;
		}
		
		std::cout << currentCommandName << " == " << currentCommandAnswer << "\n";
	}
}


// i,S,j (command)
void CommandsInterpreter::handleSelectorNameByBlockIndexAndSelectorIndexCommand() {
	if (currentArguments[1] == "S" and currentArguments[0].isNumber() and currentArguments[2].isNumber()) {
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


// i,A,? (command)
void CommandsInterpreter::handleDeclarationsCountBySectionIndexCommand() {
	if (currentArguments[1] == "A" and currentArguments[2] == "?" and currentArguments[0].isNumber()) {
		int sectionIndex = currentArguments[0].parseToInt() - 1;
		int sectionsCount = getSectionsCount();

		if (sectionIndex < 0 or sectionIndex >= sectionsCount) {
			return;
		}

		currentCommandAnswer = getDeclarationsCount(sectionIndex);

		std::cout << currentCommandName << " == " << currentCommandAnswer << "\n";
	}
}


// n,A,? (command)
void CommandsInterpreter::handlePropertyCountByPropertyNameCommand() {
	if (currentArguments[1] == "A" and currentArguments[2] == "?" and !currentArguments[0].isNumber()) {
		String propertyName = currentArguments[0];

		currentCommandAnswer = getPropertyCount(propertyName);

		std::cout << currentCommandName << " == " << currentCommandAnswer << "\n";
	}
}


// i,A,n
void CommandsInterpreter::handlePropertyValueBySectionIndexAndPropertyNameCommand() {
	if (currentArguments[1] == "A" and currentArguments[0].isNumber() and currentArguments[2].getLength() > 1) {
		int sectionIndex = currentArguments[0].parseToInt() - 1;
		String propertyName = currentArguments[2];

		std::cout << currentCommandName << " == " << getPropertyValue(sectionIndex, propertyName) << "\n";
	}
}


// z,E,n (command)
void CommandsInterpreter::handlePropertyValueBySelectorAndPropertyNameCommand() {
	if (currentArguments[1] == "E") {
		String selectorName = currentArguments[0];
		String propertyName = currentArguments[2];

		std::cout << currentCommandName << " == " << getPropertyValue(selectorName, propertyName) << "\n";
	}
}


// i,D,* (command)
void CommandsInterpreter::handleSectionDeletionCommand() {
	if (currentArguments[1] == "D" and currentArguments[2] == "*") {
		int sectionIndex = currentArguments[0].parseToInt() - 1;

		css->removeSection(sectionIndex);
		std::cout << currentCommandName << " == " << "deleted\n";
	}
}


// i,D,n (command)
void CommandsInterpreter::handlePropertyDeletionCommand() {
	if (currentArguments[1] == "D" and currentArguments[2].getLength() > 1) {
		int sectionIndex = currentArguments[0].parseToInt() - 1;
		String propertyName = currentArguments[2];

		css->removeProperty(sectionIndex, propertyName);

		std::cout << currentCommandName << " == " << "deleted\n";
	}
}

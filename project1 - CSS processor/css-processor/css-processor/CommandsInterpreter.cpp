#include "CommandsInterpreter.h"


CommandsInterpreter::CommandsInterpreter() {
	commands = List<Command>();
	css = nullptr;

	commandName = String();
	arguments = nullptr;
}


CommandsInterpreter::CommandsInterpreter(CSS* css) : css(css) {
	commands = List<Command>();

	commandName = String();
	arguments = nullptr;
}


void CommandsInterpreter::appendCommand(String commandName) {
	Command command = parseCommand(commandName);

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
	commandName = command.getCommandName();
	arguments = command.getArguments();

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


void CommandsInterpreter::printCommandResultIfNotEmpty(String commandResult) const {
	if (commandResult != "") {
		std::cout << commandName << " == " << commandResult << "\n";
	}
}


void CommandsInterpreter::printCommandResult(int commandResult) const {
	std::cout << commandName << " == " << commandResult << "\n";
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

	// if sections list is empty, return empty string
	if (sections.getHead() == nullptr) {
		return "";
	}

	for (Node<Section>* section = sections.getTail(); section != nullptr; section = section->previous) {
		List<String>* selectors = section->data.getSelectorsPointer();

		// if selectors list is empty, continue to the next section
		if (selectors->getHead() == nullptr) {
			continue;
		}

		for (Node<String>* selector = selectors->getHead(); selector != nullptr; selector = selector->next) {
			if (selector->data == selectorName) {
				List<Declaration> declarations = section->data.getDeclarations();

				// if declarations list is empty, continue to the next selector
				if (declarations.getHead() == nullptr) {
					continue;
				}

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
	if (commandName == "?") {
		std::cout << commandName << " == " << getSectionsCount() << "\n";
	}
}


// i,S,? (command)
void CommandsInterpreter::handleSelectorsCountBySectionIndexCommand() {
	if (arguments[1] == "S" and arguments[2] == "?" and arguments[0].isNumber()) {
		int sectionIndex = arguments[0].parseToInt() - 1;
		int sectionsCount = getSectionsCount();

		if (sectionIndex < 0 or sectionIndex >= sectionsCount) {
			return;
		}
		
		std::cout << commandName << " == " << getSelectorsCount(sectionIndex) << "\n";
	}
}


// z,S,? (command)
void CommandsInterpreter::handleSelectorsCountBySelectorNameCommand() {
	String selectorName = arguments[0];
	
	if (arguments[1] == "S" and arguments[2] == "?" and !selectorName.isNumber()) {

		int commandResult = getSelectorsCount(selectorName);

		printCommandResult(commandResult);
	}
}


// i,S,j (command)
void CommandsInterpreter::handleSelectorNameByBlockIndexAndSelectorIndexCommand() {
	if (arguments[1] == "S" and arguments[0].isNumber() and arguments[2].isNumber()) {
		int sectionIndex = arguments[0].parseToInt() - 1;
		int selectorIndex = arguments[2].parseToInt() - 1;
		int sectionsCount = getSectionsCount();

		if (sectionIndex < 0 or sectionIndex >= sectionsCount) {
			return;
		}

		int selectorsCount = getSelectorsCount(sectionIndex);

		if (selectorIndex < 0 or selectorIndex >= selectorsCount) {
			return;
		}

		String commandAnswer = getSelectorName(sectionIndex, selectorIndex);

		printCommandResultIfNotEmpty(commandAnswer);
	}
}


// i,A,? (command)
void CommandsInterpreter::handleDeclarationsCountBySectionIndexCommand() {
	if (arguments[1] == "A" and arguments[2] == "?" and arguments[0].isNumber()) {
		int sectionIndex = arguments[0].parseToInt() - 1;
		int sectionsCount = getSectionsCount();

		if (sectionIndex < 0 or sectionIndex >= sectionsCount) {
			return;
		}

		int commandAnswer = getDeclarationsCount(sectionIndex);

		printCommandResult(commandAnswer);
	}
}


// n,A,? (command)
void CommandsInterpreter::handlePropertyCountByPropertyNameCommand() {
	if (arguments[1] == "A" and arguments[2] == "?" and !arguments[0].isNumber()) {
		String propertyName = arguments[0];

		int commandResult = getPropertyCount(propertyName);

		printCommandResult(commandResult);
	}
}


// i,A,n
void CommandsInterpreter::handlePropertyValueBySectionIndexAndPropertyNameCommand() {
	if (arguments[1] == "A" and arguments[0].isNumber() and arguments[2].getLength() > 1) {
		int sectionIndex = arguments[0].parseToInt() - 1;
		String propertyName = arguments[2];

		String commandResult = getPropertyValue(sectionIndex, propertyName);

		printCommandResultIfNotEmpty(commandResult);
	}
}


// z,E,n (command)
void CommandsInterpreter::handlePropertyValueBySelectorAndPropertyNameCommand() {
	if (arguments[1] == "E") {
		String selectorName = arguments[0];
		String propertyName = arguments[2];

		String commandResult = getPropertyValue(selectorName, propertyName);

		printCommandResultIfNotEmpty(commandResult);
	}
}


// i,D,* (command)
void CommandsInterpreter::handleSectionDeletionCommand() {
	if (arguments[1] == "D" and arguments[2] == "*") {
		int sectionIndex = arguments[0].parseToInt() - 1;

		css->removeSection(sectionIndex);
		std::cout << commandName << " == " << "deleted\n";
	}
}


// i,D,n (command)
void CommandsInterpreter::handlePropertyDeletionCommand() {
	if (arguments[1] == "D" and arguments[2].getLength() > 1) {
		int sectionIndex = arguments[0].parseToInt() - 1;
		String propertyName = arguments[2];

		css->removeProperty(sectionIndex, propertyName);

		std::cout << commandName << " == " << "deleted\n";
	}
}

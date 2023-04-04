#pragma once


#include "String.h"
#include "List.h"
#include "CSS.h"
#include "Command.h"


class CommandsInterpreter
{
private:
	List<Command> commands;
	CSS* css;

	String currentCommandName;
	String* currentArguments;
	String currentCommandAnswer;

public:
	CommandsInterpreter();
	CommandsInterpreter(CSS* css);

	void appendCommand(String commandString);
	Command parseCommand(String commandString);
	void printCommands();

	void executeCommands();
	void executeCommand(Command command);

	bool isArgumentNumber(String argument);

	void setCSS(CSS* css);

	// Commands
	// ? (command)
	int getSectionsCount(); 
	void handleSectionsCountCommand();
	
	// i,S,? (command)
	int getSelectorsCount(int sectionIndex);
	void handleSelectorsCountBySectionIndexCommand();

	// z,S,? (command)
	int getSelectorsCount(String selectorName);
	void handleSelectorsCountBySelectorNameCommand();

	// i,S,j (command)
	String getSelectorName(int sectionIndex, int selectorIndex); // !!! SHOULD BE BLOCK INDEX
	void handleSelectorNameByBlockIndexAndSelectorIndexCommand();
	
	// i,A,? (command)
	int getDeclarationsCount(int sectionIndex); 

	// i,A,n (command)
	String getPropertyValue(int sectionIndex, String propertyName); 

	// z,E,n (command)
	String getPropertyValue(String selectorName, String propertyName);
};

/* COMMANDS TO COVER

? – wypisz liczbê sekcji CSS;
[implemented, tests needed]

i,S,? – wypisz liczbê selektorów dla sekcji nr i (numery zaczynaj¹ siê od 1), jeœli nie ma takiego bloku pomiñ;
[implemented, tests needed]

i,A,? - wypisz liczbê atrybutów dla sekcji nr i, jeœli nie ma takiego bloku lub sekcji pomiñ;
[implemented, tests needed]

i,S,j – wypisz j-ty selector dla i-tego bloku (numery sekcji oraz atrybutów zaczynaj¹ siê od 1) jeœli nie ma sekcji lub selektora pomiñ;
(!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!)
implement blocks
(!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!)

i,A,n – wypisz dla i-tej sekcji wartoœæ atrybutu o nazwie n, jeœli nie ma takiego pomiñ;
[implemented, tests needed]

n,A,? – wypisz ³¹czn¹ (dla wszystkich bloków) liczbê wyst¹pieñ atrybutu nazwie n. (W ramach pojedynczego bloku duplikaty powinny zostaæ usuniête na etapie wczytywania). Mo¿liwe jest 0;
(!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!)

z,S,? – wypisz ³¹czn¹ (dla wszystkich bloków) liczbê wyst¹pieñ selektora z. Mo¿liwe jest 0;
[implemented, tests needed]

z,E,n – wypisz wartoœæ atrybutu o nazwie n dla selektora z, w przypadku wielu wyst¹pieñ selektora z bierzemy ostatnie. W przypadku braku pomiñ;
(!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!)

i,D,* - usuñ ca³¹ sekcjê nr i (tj. separatory+atrybuty), po poprawnym wykonaniu wypisz deleted;
[implemented, tests needed]

i,D,n – usuñ z i-tej sekcji atrybut o nazwie n, jeœli w wyniku operacji pozostaje pusta sekcja powinna zostaæ równie¿ usuniêta (wraz z ew. selektorami), po poprawnym wykonaniu wypisz deleted.
[implemented, tests needed]

*/

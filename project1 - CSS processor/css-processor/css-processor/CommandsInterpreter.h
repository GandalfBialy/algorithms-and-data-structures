#pragma once


#include "String.h"
#include "List.h"
#include "CSS.h"


class CommandsInterpreter
{
private:
	List<String> commands;

public:
	CommandsInterpreter();

	void executeCommands(CSS css);

	void appendCommand(String command);

	int getSectionsCount(CSS css); // ? (command)
	int getSelectorsCount(CSS css, int sectionIndex); // i,S,? (command)
	int getDeclarationsCount(CSS css, int sectionIndex, int selectorIndex); // i,A,? (command)

	void printCommands();
};

/* COMMANDS TO COVER

? – wypisz liczbê sekcji CSS;
[implemented, tests needed]

i,S,? – wypisz liczbê selektorów dla sekcji nr i (numery zaczynaj¹ siê od 1), jeœli nie ma takiego bloku pomiñ;
[implemented, tests needed]

i,A,? - wypisz liczbê atrybutów dla sekcji nr i, jeœli nie ma takiego bloku lub sekcji pomiñ;
[implemented, tests needed]

i,S,j – wypisz j-ty selector dla i-tego bloku (numery sekcji oraz atrybutów zaczynaj¹ siê od 1) jeœli nie ma sekcji lub selektora pomiñ;

i,A,n – wypisz dla i-tej sekcji wartoœæ atrybutu o nazwie n, jeœli nie ma takiego pomiñ;

n,A,? – wypisz ³¹czn¹ (dla wszystkich bloków) liczbê wyst¹pieñ atrybutu nazwie n. (W ramach pojedynczego bloku duplikaty powinny zostaæ usuniête na etapie wczytywania). Mo¿liwe jest 0;

z,S,? – wypisz ³¹czn¹ (dla wszystkich bloków) liczbê wyst¹pieñ selektora z. Mo¿liwe jest 0;

z,E,n – wypisz wartoœæ atrybutu o nazwie n dla selektora z, w przypadku wielu wyst¹pieñ selektora z bierzemy ostatnie. W przypadku braku pomiñ;

i,D,* - usuñ ca³¹ sekcjê nr i (tj. separatory+atrybuty), po poprawnym wykonaniu wypisz deleted;

i,D,n – usuñ z i-tej sekcji atrybut o nazwie n, jeœli w wyniku operacji pozostaje pusta sekcja powinna zostaæ równie¿ usuniêta (wraz z ew. selektorami), po poprawnym wykonaniu wypisz deleted.

*/

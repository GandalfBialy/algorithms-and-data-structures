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

? � wypisz liczb� sekcji CSS;
[implemented, tests needed]

i,S,? � wypisz liczb� selektor�w dla sekcji nr i (numery zaczynaj� si� od 1), je�li nie ma takiego bloku pomi�;
[implemented, tests needed]

i,A,? - wypisz liczb� atrybut�w dla sekcji nr i, je�li nie ma takiego bloku lub sekcji pomi�;
[implemented, tests needed]

i,S,j � wypisz j-ty selector dla i-tego bloku (numery sekcji oraz atrybut�w zaczynaj� si� od 1) je�li nie ma sekcji lub selektora pomi�;

i,A,n � wypisz dla i-tej sekcji warto�� atrybutu o nazwie n, je�li nie ma takiego pomi�;

n,A,? � wypisz ��czn� (dla wszystkich blok�w) liczb� wyst�pie� atrybutu nazwie n. (W ramach pojedynczego bloku duplikaty powinny zosta� usuni�te na etapie wczytywania). Mo�liwe jest 0;

z,S,? � wypisz ��czn� (dla wszystkich blok�w) liczb� wyst�pie� selektora z. Mo�liwe jest 0;

z,E,n � wypisz warto�� atrybutu o nazwie n dla selektora z, w przypadku wielu wyst�pie� selektora z bierzemy ostatnie. W przypadku braku pomi�;

i,D,* - usu� ca�� sekcj� nr i (tj. separatory+atrybuty), po poprawnym wykonaniu wypisz deleted;

i,D,n � usu� z i-tej sekcji atrybut o nazwie n, je�li w wyniku operacji pozostaje pusta sekcja powinna zosta� r�wnie� usuni�ta (wraz z ew. selektorami), po poprawnym wykonaniu wypisz deleted.

*/

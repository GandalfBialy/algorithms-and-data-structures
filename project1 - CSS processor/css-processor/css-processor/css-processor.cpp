#include <iostream>


#include "Node.h"
#include "List.h"
#include "String.h"
//#include "Parser.h"
//#include "CSS.h"


void testList() {
	List<int> integersList;
	integersList.insert(1);
	integersList.insert(2);
	integersList.insert(3);
	integersList.insert(4);
	integersList.insert(5);
	std::cout << integersList;

	List<String> stringsList;
	stringsList.insert("Hello");
	stringsList.insert("World");
	stringsList.insert("!");
	std::cout << stringsList;

	List<List<int>> listOfIntegersLists;
	listOfIntegersLists.insert(integersList);
	listOfIntegersLists.insert(integersList);
	listOfIntegersLists.insert(integersList);
	listOfIntegersLists.print();

	List<List<String>> stringListList;
	stringListList.insert(stringsList);
	stringListList.insert(stringsList);
	stringListList.insert(stringsList);
	stringListList.print();
}



void testString() {
	String string1 = "Hello";
	String string1Copy = string1;
	String string2 = "World";
	String string3 = string1 + " " + string2;
	String string4 = "Vivat";
	string4 += " ";
	string4 += string3;

	std::cout << string1 << std::endl;
	std::cout << string1Copy << std::endl;
	std::cout << string2 << std::endl;
	std::cout << string3 << std::endl;
	std::cout << string4 << std::endl;

	for (int i = 0; i < 5; i++) {
		std::cout << string1[i] << std::endl;
	}
	
	std::cout << string1.getLength() << std::endl;
	std::cout << string2.getLength() << std::endl;
	std::cout << string3.getLength() << std::endl;
	std::cout << string4.getLength() << std::endl;

	std::cout << (string1 == string1Copy) << std::endl;
	std::cout << (string1 == string2) << std::endl;
}


int main()
{
	testList();
	//testString();

	//Parser parser;
	//parser.loadCSS();

	return 0;
}

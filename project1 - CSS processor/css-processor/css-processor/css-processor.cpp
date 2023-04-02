#include <iostream>


#include "Node.h"
#include "List.h"
#include "String.h"
#include "Parser.h"
#include "CSS.h"


namespace tests {
	void testList() {
		List<int> integersList;
		integersList.append(1);
		integersList.append(2);
		integersList.append(3);
		integersList.append(4);
		integersList.append(5);
		std::cout << integersList;

		List<String> stringsList;
		stringsList.append("Hello");
		stringsList.append("World");
		stringsList.append("!");
		std::cout << stringsList;

		List<List<int>> listOfIntegersLists;
		listOfIntegersLists.append(integersList);
		listOfIntegersLists.append(integersList);
		listOfIntegersLists.append(integersList);
		listOfIntegersLists.print();

		List<List<String>> stringListList;
		stringListList.append(stringsList);
		stringListList.append(stringsList);
		stringListList.append(stringsList);
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


	void runTests() {
		testList();
		testString();
	}
}


int main()
{
	//tests::runTests();

	Parser parser;
	parser.loadCSS();
	parser.parseCSS();

	return 0;
}

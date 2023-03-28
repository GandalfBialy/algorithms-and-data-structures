#include <iostream>


#include "Node.h"
#include "List.h"
#include "String.h"


void testList() {
	Node* head = new Node();
	head->data = 1;
	head->next = NULL;
	head->previous = NULL;

	for (int i = 2; i < 10; i++) {
		list::insertNode(head, i);
	}
	list::print(head);

	std::cout << "insertNodeAtBeginning(&head, 0)" << std::endl;
	list::insertNodeAtBeginning(&head, 0);
	list::print(head);

	std::cout << "insertNodeAfter(head->next->next, 300)" << std::endl;
	list::insertNodeAfter(head->next->next, 300);
	list::print(head);

	std::cout << "deleteNode(&head, head->next->next)" << std::endl;
	list::deleteNode(&head, head->next->next);
	list::print(head);

	std::cout << "deleteNodeAtPosition(&head, 3)" << std::endl;
	list::deleteNodeAtPosition(&head, 3);
	list::print(head);

	std::cout << "clearList(&head)" << std::endl;
	list::clearList(&head);
	list::print(head);

	delete head;
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
	testString();

	return 0;
}

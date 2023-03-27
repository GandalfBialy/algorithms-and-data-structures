#include <iostream>


#include "Node.h"
#include "List.h"


int main()
{
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

	return 0;
}

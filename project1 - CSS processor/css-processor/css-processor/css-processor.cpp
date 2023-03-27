#include <iostream>


#include "Node.h"


void printList(Node* head)
{
	Node* currentNode = head;

	while (currentNode != NULL) {
		std::cout << currentNode->data << " ";
		currentNode = currentNode->next;
	}

	std::cout << std::endl;
}


void insertNode(Node* head, int data)
{
	Node* currentNode = head;

	while (currentNode->next != NULL) {
		currentNode = currentNode->next;
	}

	Node* newNode = new Node();
	newNode->data = data;
	newNode->next = NULL;
	newNode->previous = currentNode;

	currentNode->next = newNode;
}


void insertNodeAtBeginning(Node** head, int data)
{
	Node* newNode = new Node();
	newNode->data = data;
	newNode->next = *head;
	newNode->previous = NULL;

	if (*head != NULL) {
		(*head)->previous = newNode;
	}

	*head = newNode;
}



int main()
{
	Node* head = new Node();
	head->data = 1;
	head->next = NULL;
	head->previous = NULL;
	
	insertNode(head, 2);
	insertNode(head, 3);
	insertNode(head, 4);
	insertNode(head, 5);
	
	printList(head);
	
	return 0;
}

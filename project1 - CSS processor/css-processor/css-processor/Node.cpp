#include "Node.h"


#include <iostream>


namespace list {
	static void print(Node* head)
	{
		Node* currentNode = head;

		std::cout << "List: ";

		while (currentNode != NULL) {
			std::cout << currentNode->data;

			if (currentNode->next != NULL) {
				std::cout << ", ";
			}

			currentNode = currentNode->next;
		}

		std::cout << std::endl << std::endl;
	}

	
	static void insertNode(Node* head, int data)
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


	static void insertNodeAtBeginning(Node** head, int data)
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


	static void insertNodeAfter(Node* previousNode, int data)
	{
		if (previousNode == NULL) {
			std::cout << "The given previous node cannot be NULL" << std::endl;
			return;
		}

		Node* newNode = new Node();
		newNode->data = data;
		newNode->next = previousNode->next;
		newNode->previous = previousNode;

		previousNode->next = newNode;

		if (newNode->next != NULL) {
			newNode->next->previous = newNode;
		}
	}


	static void deleteNode(Node** head, Node* nodeToDelete)
	{
		if (*head == NULL || nodeToDelete == NULL) {
			return;
		}

		if (*head == nodeToDelete) {
			*head = nodeToDelete->next;
		}

		if (nodeToDelete->next != NULL) {
			nodeToDelete->next->previous = nodeToDelete->previous;
		}

		if (nodeToDelete->previous != NULL) {
			nodeToDelete->previous->next = nodeToDelete->next;
		}

		delete nodeToDelete;
	}


	static void deleteNodeAtPosition(Node** head, int position)
	{
		if (*head == NULL) {
			return;
		}

		Node* currentNode = *head;

		for (int i = 0; currentNode != NULL && i < position - 1; i++) {
			currentNode = currentNode->next;
		}

		if (currentNode == NULL || currentNode->next == NULL) {
			return;
		}

		Node* nodeToDelete = currentNode->next;

		currentNode->next = nodeToDelete->next;

		if (nodeToDelete->next != NULL) {
			nodeToDelete->next->previous = currentNode;
		}

		delete nodeToDelete;
	}
}

#pragma once


#include "Node.h"


template <typename T>
class List
{
private:
	Node<T>* head;
	int size;

	template <typename U>
	friend std::ostream& operator<<(std::ostream& os, const List<U>& list);

public:
	List() {
		head = nullptr;
		size = 0;
	}


	void print() {
		for (Node<T>* current = head; current != nullptr; current = current->next) {
			std::cout << current->data << " ";
		}

		std::cout << std::endl;
	}


	void append(T data) {
		Node<T>* node = new Node<T>(data);

		if (head == nullptr) {
			head = node;
		}
		else {
			Node<T>* current = head;

			while (current->next != nullptr) {
				current = current->next;
			}

			current->next = node;
		}

		size++;
	}


	void remove(T data) {
		if (head == nullptr) {
			return;
		}

		if (head->data == data) {
			Node<T>* temp = head;
			head = head->next;
			delete temp;
			size--;
			return;
		}

		Node<T>* currentNode = head;

		while (currentNode->next != nullptr and currentNode->next->data != data) {
			currentNode = currentNode->next;
		}

		if (currentNode->next != nullptr) {
			Node<T>* temp = currentNode->next;
			currentNode->next = currentNode->next->next;
			delete temp;
			size--;
		}
	}


	int getSize() {
		return size;
	}





	






	/*static void insertNodeAtBeginning(Node** head, int data)
	{
		Node<T>* newNode = new Node();
		newNode->data = data;
		newNode->next = *head;
		newNode->previous = NULL;

		if (*head != NULL) {
			(*head)->previous = newNode;
		}

		*head = newNode;
	}*/


	/*static void insertNodeAfter(Node* previousNode, int data)
	{
		if (previousNode == NULL) {
			std::cout << "The given previous node cannot be NULL" << std::endl;
			return;
		}

		Node<T>* newNode = new Node();
		newNode->data = data;
		newNode->next = previousNode->next;
		newNode->previous = previousNode;

		previousNode->next = newNode;

		if (newNode->next != NULL) {
			newNode->next->previous = newNode;
		}
	}*/


	/*static void deleteNode(Node** head, Node* nodeToDelete)
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
	}*/


	/*static void clearList(Node** head)
	{
		Node* currentNode = *head;
		Node* nextNode = NULL;

		while (currentNode != NULL) {
			nextNode = currentNode->next;
			delete currentNode;
			currentNode = nextNode;
		}

		*head = NULL;
	}*/
};




template<typename T>
std::ostream& operator<<(std::ostream& outputStream, const List<T>& list) {
	Node<T>* current = list.head;

	while (current != nullptr) {
		outputStream << current->data << " ";
		current = current->next;
	}

	outputStream << std::endl;
	return outputStream;
}

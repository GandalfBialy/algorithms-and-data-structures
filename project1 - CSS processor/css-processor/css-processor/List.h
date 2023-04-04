#pragma once


#include "Node.h"


template <typename T>
class List
{
private:
	Node<T>* head;
	//Node<T>* tail;
	int size;

	template <typename U>
	friend std::ostream& operator<<(std::ostream& os, const List<U>& list);

public:
	List();

	void print();
	void append(T data);

	T front();
	T back();

	void popFront();

	void remove(T data);

	Node<T>* getHead();
	int getSize();

	// assign operator
	List<T>& operator=(const List<T>& list) {
		if (this != &list) {
			this->head = list.head;
			this->size = list.size;
		}
		return *this;
	}

	// subscript operator
	T& operator[](int index) {
		Node<T>* currentNode = head;

		for (int i = 0; i < index; i++) {
			currentNode = currentNode->next;
		}

		return currentNode->data;
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
			std::cerr << "The given previous node cannot be NULL" << std::endl;
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
List<T>::List() {
	head = nullptr;
	size = 0;
}


template<typename T>
void List<T>::print() {
	for (Node<T>* current = head; current != nullptr; current = current->next) {
		std::cerr << current->data << " ";
	}

	std::cerr << std::endl;
}


template<typename T>
void List<T>::append(T data) {
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


template<typename T>
T List<T>::front() {
	return head->data;
}


template<typename T>
T List<T>::back() {
	Node<T>* current = head;

	while (current->next != nullptr) {
		current = current->next;
	}

	return current->data;
}


template<typename T>
void List<T>::popFront() {
	if (head == nullptr) {
		return;
	}

	Node<T>* temp = head;
	head = head->next;
	
	size--;
	delete temp;
}


template<typename T>
void List<T>::remove(T data) {
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


template<typename T>
int List<T>::getSize() {
	return size;
}


template<typename T>
Node<T>* List<T>::getHead() {
	return head;
}


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

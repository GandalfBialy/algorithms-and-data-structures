#pragma once


#include "Node.h"


template <typename T>
class List
{
private:
	Node<T>* head;
	Node<T>* tail;
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
	void removeAt(int index);
	void clear();

	Node<T>* getHead();
	Node<T>* getTail();
	int getSize();

	
	List<T>& operator=(const List<T>& list) {
		if (this != &list) {
			this->head = list.head;
			this->size = list.size;
		}
		return *this;
	}

	
	T& operator[](int index) {
		Node<T>* currentNode = head;

		for (int i = 0; i < index; i++) {
			currentNode = currentNode->next;
		}

		return currentNode->data;
	}
};


template<typename T>
List<T>::List() {
	head = nullptr;
	tail = nullptr;
	size = 0;
}


template<typename T>
void List<T>::print() {
	Node<T>* current = head;

	while (current != nullptr) {
		std::cout << current->data << " ";
		current = current->next;
	}

	std::cout << std::endl;
}


template<typename T>
void List<T>::append(T data) {
	Node<T>* newNode = new Node<T>(data);

	if (head == nullptr) {
		head = newNode;
		tail = newNode;
	}
	else {
		tail->next = newNode;
		tail = newNode;
	}

	size++;
}


template<typename T>
T List<T>::front() {
	return head->data;
}


template<typename T>
T List<T>::back() {
	return tail->data;
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
void List<T>::removeAt(int index) {
	if (head == nullptr) {
		return;
	}

	if (index == 0) {
		Node<T>* temp = head;
		head = head->next;

		size--;
		delete temp;

		return;
	}

	Node<T>* currentNode = head;

	for (int i = 0; i < index - 1; i++) {
		currentNode = currentNode->next;
	}

	if (currentNode->next != nullptr) {
		Node<T>* temp = currentNode->next;
		currentNode->next = currentNode->next->next;

		size--;
		delete temp;
	}
}


template<typename T>
void List<T>::clear() {
	while (head != nullptr) {
		Node<T>* temp = head;
		head = head->next;
		delete temp;
	}

	size = 0;
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
Node<T>* List<T>::getTail() {
	return tail;
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

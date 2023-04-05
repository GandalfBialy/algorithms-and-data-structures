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
	//~List();

	void print();
	void append(T data);

	T front();
	T back();

	void popFront();

	void removeFront();
	void removeBack();
	bool remove(T data);
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


//template<typename T>
//List<T>::~List() {
//	while (head != nullptr) {
//		Node<T>* temp = head;
//		head = head->next;
//		delete temp;
//	}
//
//	tail = nullptr;
//}


template<typename T>
void List<T>::print() {
	Node<T>* current = head;

	while (current != nullptr) {
		std::cerr << current->data << " ";
		current = current->next;
	}

	std::cerr << std::endl;
}


template<typename T>
void List<T>::append(T data) {
	Node<T>* newNode = new Node<T>(data);

	if (head == nullptr) {
		head = newNode;
		tail = newNode;
	}
	else {
		newNode->previous = tail;
		tail->next = newNode;
		tail = newNode;
	}

	size++;
	
	
	/*Node<T>* newNode = new Node<T>(data);

	if (head == nullptr) {
		head = newNode;
		tail = newNode;
	}
	else {
		tail->next = newNode;
		newNode->previous = tail;
		tail = newNode;
	}

	size++;*/
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
void List<T>::removeFront() {
	if (head == nullptr) {
		return;
	}

	Node<T>* temp = head;
	head = head->next;

	if (head != nullptr) {
		head->previous = nullptr;
	}
	else {
		tail = nullptr;
	}

	size--;
	delete temp;
}


template<typename T>
void List<T>::removeBack() {
	if (tail == nullptr) {
		return;
	}

	Node<T>* temp = tail;
	tail = tail->previous;

	if (tail != nullptr) {
		tail->next = nullptr;
	}
	else {
		head = nullptr;
	}
	
	size--;
	delete temp;
}


template<typename T>
bool List<T>::remove(T data) {
	Node* current = head;
	while (current != nullptr) {
		if (current->data == data) {
			if (current->previous != nullptr) {
				current->previous->next = current->next;
			}
			else {
				head = current->next;
			}
			if (current->next != nullptr) {
				current->next->previous = current->previous;
			}
			else {
				tail = current->previous;
			}

			size--;
			delete current;
			
			return true;
		}

		current = current->next;
	}

	return false;
}


template<typename T>
void List<T>::removeAt(int index) {
	if (index < 0 || index >= size) {
		std::cerr << "Index out of bounds!" << std::endl;
		return;
	}

	if (index == 0) {
		removeFront();
		return;
	}

	if (index == size - 1) {
		removeBack();
		return;
	}

	Node<T>* current = head;
	for (int i = 0; i < index; i++) {
		current = current->next;
	}

	current->previous->next = current->next;
	current->next->previous = current->previous;
	delete current;
	size--;

	/*if (index < 0 || index >= size) {
		return;
	}

	Node* current = head;

	for (int i = 0; i < index; i++) {
		current = current->next;
	}

	if (current == head) {
		head = head->next;

		if (head) {
			head->previous = nullptr;
		}
		else {
			tail = nullptr;
		}
	}
	else if (current == tail) {
		tail = tail->previous;
		tail->next = nullptr;
	}
	else {
		current->previous->next = current->next;
		current->next->previous = current->previous;
	}

	size--;
	delete current;*/
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

#include <iostream>

using namespace std;

struct Node {
	int data;
	Node* next;
};

void pushFront(Node** headPointer, int value) {
	Node* newNode = new Node;

	newNode->data = value;
	newNode->next = *headPointer;
	*headPointer = newNode;
}

void pushBack(Node*& head, int value) {
	Node* newNode, * tempNode;

	tempNode = new Node;
	tempNode->data = value;
	tempNode->next = NULL;

	newNode = head;

	if (newNode) {
		while (newNode->next) {
			newNode = newNode->next;
		}
		newNode->next = tempNode;
	}
	else {
		head = tempNode;
	}
	
}

void printList(Node* head) {
	while (head != NULL) {
		cout << head->data << " ";
		head = head->next;
	}

	cout << endl;
}

int main()
{
	Node* head = NULL;

	for (int i = 0; i < 10; i++) {
		pushFront(&head, i * 2);
		pushBack(head, i * 2 + 1);
		printList(head);
	}
}
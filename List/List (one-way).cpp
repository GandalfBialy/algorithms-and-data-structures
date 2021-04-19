#include <iostream>

using namespace std;

struct slistEl {
	slistEl* next;
	char data;
};

void l_push_front(slistEl*& head, char v) {
	slistEl* p = new slistEl;

	p->data = v;
	p->next = head;
	head = p;
}

void l_pop_front(slistEl*& head) {
	slistEl* p;
	p = head;
	if (p) {
		head = p->next;
		delete p;
	}
}

void l_push_back(slistEl*& head, char v) {
	slistEl* p, * e;

	e = new slistEl;
	e->next = NULL;
	e->data = v;
	p = head;
	if (p) {
		while (p->next) p = p->next;
		p->next = e;
	}
	else {
		head = e;
	}
}

void l_pop_back(slistEl*& head) {
	slistEl* p = head;
	if (p) {
		if (p->next) {
			while (p->next->next) {
				p = p->next;
			}
			delete p->next;
			p->next = NULL;
		}
		else {
			delete p;
			head = NULL;
		}
	}
}

void l_insert_before(slistEl*& head, slistEl* e, char v) {
	slistEl* p = head;

	if (p == e) {
		l_push_front(head, v);
	}
	else {
		while (p->next != e) {
			p = p->next;
		}
		p->next = new slistEl;
		p->next->next = e;
		p->next->data = v;
	}
}

void l_insert_after(slistEl* e, char v) {
	slistEl* p = new slistEl;

	p->next = e->next;
	p->data = v;
	e->next = p;
}

void l_remove(slistEl*& head, slistEl* e) {
	slistEl* p;

	if (head == e) {
		l_pop_front(head);
	}
	else {
		p = head;
		while (p->next != e) {
			p = p->next;
		}
		p->next = e->next;
		delete e;
	}
}

unsigned l_size(slistEl* p) {
	unsigned c = 0;

	while (p) {
		c++;
		p = p->next;
	}
	return c;
}

void l_printl(slistEl* p) {
	unsigned i;

	cout << "Number of elements : " << l_size(p) << endl;

	for (i = 1; p; p = p->next) {
		cout << "Element #" << i++ << "  data = " << p->data << endl;
	}
	cout << endl;
}

int main()
{
	slistEl* L = NULL; // zawiera adres pocz¹tku listy
	slistEl* e;        // do wskazywania elementów listy
	char i;

	for (i = 'A'; i <= 'G'; i++) {
		l_push_back(L, i);
	}
	l_printl(L);

	// Przechodzimy do elementu o wartoœci D
	e = L;

	for (i = 'A'; i <= 'C'; i++) {
		e = e->next;
	}

	// Przed elementem D umieszczamy +
	l_insert_before(L, e, '+');

	// Za elementem D umieszczamy *
	l_insert_after(e, '*');

	l_printl(L);

	// Usuwamy element D oraz element pierwszy i ostatni
	l_remove(L, e);
	l_pop_front(L);
	l_pop_back(L);
	l_printl(L);
}
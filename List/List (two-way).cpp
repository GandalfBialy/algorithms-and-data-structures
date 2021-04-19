#include <iostream>
#include <iomanip>

using namespace std;

struct dlistEl
{
	dlistEl* next, * prev;
	int data;
};

struct dlistVar
{
	dlistEl* head, * tail;
	unsigned int count;
};


void l_push_front(dlistVar& L, char v) {
	dlistEl* p;

	p = new dlistEl;
	p->data = v;
	p->prev = NULL;
	p->next = L.head;
	L.head = p;
	L.count++;
	if (p->next) p->next->prev = p;
	else L.tail = p;
}

void l_push_back(dlistVar& L, char v) {
	dlistEl* p;

	p = new dlistEl;
	p->data = v;
	p->next = NULL;
	p->prev = L.tail;
	L.tail = p;
	L.count++;
	if (p->prev) p->prev->next = p;
	else L.head = p;
}

void l_insert_before(dlistVar& L, dlistEl* e, char v) {
	dlistEl* p;

	if (e == L.head) {
		l_push_front(L, v);
	}
	else {
		p = new dlistEl;
		p->data = v;
		p->next = e;
		p->prev = e->prev;
		L.count++;
		e->prev->next = p;
		e->prev = p;
	}
}

void l_insert_after(dlistVar& L, dlistEl* e, char v) {
	dlistEl* p;

	if (e == L.tail) {
		l_push_back(L, v);
	}
	else {
		p = new dlistEl;
		p->data = v;
		p->next = e->next;
		p->prev = e;
		L.count++;
		e->next->prev = p;
		e->next = p;
	}
}

void l_remove(dlistVar& L, dlistEl* e) {
	L.count--;
	if (e->prev) {
		e->prev->next = e->next;
	}
	else {
		L.head = e->next;
	}

	if (e->next) {
		e->next->prev = e->prev;
	}
	else {
		L.tail = e->prev;
	}
	delete e;
}

void l_pop_front(dlistVar& L) {
	if (L.count) {
		l_remove(L, L.head);
	}
}

void l_pop_back(dlistVar& L) {
	if (L.count) {
		l_remove(L, L.tail);
	}
}

void l_printl(dlistVar& L) {
	dlistEl* p;

	cout << setw(3) << L.count << ": [ ";
	p = L.head;
	while (p) {
		cout << " " << p->data;
		p = p->next;
	}
	cout << " ] \n\n";
}

void l_init(dlistVar& L) {
	L.head = L.tail = NULL;
	L.count = 0;
}


int main()
{
	dlistVar L;
	char i;

	l_init(L);  // inicjujemy zmienn¹ obs³ugi listy

	for (i = 'A'; i <= 'C'; i++) l_push_front(L, i);
	l_printl(L);
	for (i = 'D'; i <= 'F'; i++) l_push_back(L, i);
	l_printl(L);
	l_insert_before(L, L.tail, '#');
	l_printl(L);
	l_insert_after(L, L.head, '%');
	l_printl(L);
	l_pop_front(L);
	l_printl(L);
	l_pop_back(L);
	l_printl(L);
	l_remove(L, L.head->next->next);
	l_printl(L);
}
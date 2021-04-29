// Stos na liœcie jednokierunkowej
// Data: 13.08.2012
// (C)2020 mgr Jerzy Wa³aszek
//------------------------------

#include <iostream>

using namespace std;

// Definicja typu obiektowego stack
//---------------------------------

struct slistEl {
    slistEl* next;
    int data;
};

class stack {
private:
    slistEl* S;   // lista przechowuj¹ca stos

public:
    stack();       // konstruktor
    ~stack();      // destruktor
    bool empty(void);
    slistEl* top(void);
    void push(int v);
    void pop(void);
};

//---------------------
// Metody obiektu stack
//---------------------

// Konstruktor
//------------

stack::stack() {
    S = NULL;
}

// Destruktor - zwalnia tablicê dynamiczn¹
//----------------------------------------

stack::~stack() {
    while (S) pop();
}

// Sprawdza, czy stos jest pusty
//------------------------------

bool stack::empty(void) {
    return !S;
}

// Zwraca szczyt stosu
//--------------------

slistEl* stack::top(void) {
    return S;
}

// Zapisuje na stos
//-----------------

void stack::push(int v) {
    slistEl* e = new slistEl;
    e->data = v;
    e->next = S;
    S = e;
}

// Usuwa ze stosu
//---------------

void stack::pop(void) {
    if (S) {
        slistEl* e = S;
        S = S->next;
        delete e;
    }
}

//---------------
// Program g³ówny
//---------------

int main()
{
    stack S;
    int i;

    for (i = 1; i <= 10; i++) {
        S.push(i);
    }

    while (!S.empty()) {
        cout << S.top()->data << endl;
        S.pop();
    }
}
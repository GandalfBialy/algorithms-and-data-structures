// Odwracanie zawartoœci listy jednokierunkowej
// Data: 20.02.2012
// (C)2020 mgr Jerzy Wa³aszek
//---------------------------------------------

#include <iostream>

using namespace std;

// Typ elementów listy
//--------------------
struct slistEl
{
    slistEl* next;
    char data;
};

// Definicja typu obiektowego slist
//---------------------------------

class slist
{
public:
    slistEl* head;

    slist();  // konstruktor
    ~slist(); // destruktor
    void printl();
    void push_front(char v);
    void pop_front();
    void reverse();
};

// Konstruktor listy
//------------------
slist::slist()
{
    head = NULL;
}

// Destruktor listy
//-----------------
slist::~slist()
{
    while (head) pop_front();
}


// Procedura wyœwietla zawartoœæ elementów listy
//----------------------------------------------
void slist::printl()
{
    unsigned i;
    slistEl* p = head;

    for (i = 1; p; p = p->next) cout << p->data;
    cout << endl;
}

// Procedura do³¹czania na pocz¹tek listy
//---------------------------------------
void slist::push_front(char v)
{
    slistEl* p;

    p = new slistEl;
    p->next = head;
    p->data = v;
    head = p;
}

// Procedura usuwa pierwszy element
//---------------------------------
void slist::pop_front()
{
    slistEl* p = head; // zapamiêtujemy pocz¹tek

    if (p)
    {
        head = p->next;   // nowy pocz¹tek
        delete p;         // usuñ element z pamiêci
    }
}

// Odwraca elementy na liœcie
//---------------------------
void slist::reverse() {
    slistEl* p, * pc;

    if (head) {
        pc = head;
        while (pc->next) {
            p = pc->next;
            pc->next = p->next;
            p->next = head;
            head = p;
        }
    }
}

int main()
{
    slist L;
    int i;

    for (i = 25; i >= 0; i--) L.push_front(65 + i);
    L.printl();
    L.reverse();
    L.printl();

    return 0;
}
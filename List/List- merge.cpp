// Scalanie dwóch posortowanych list jednokierunkowych
// Data: 25.02.2012
// (C)2020 mgr Jerzy Wa³aszek
//----------------------------------------------------

#include <iostream>
#include <cstdlib>
#include <ctime>

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
    unsigned size();
    void printl();
    void push_front(char v);
    void pop_front();
    void merge(slist& l1, slist& l2);
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

// Funkcja oblicza liczbê elementów listy
//---------------------------------------
unsigned slist::size()
{
    unsigned c = 0;
    slistEl* p = head;
    while (p)
    {
        c++;
        p = p->next;
    }
    return c;
}

// Procedura wyœwietla zawartoœæ elementów listy
//----------------------------------------------
void slist::printl()
{
    slistEl* p;

    cout << size() << ": ";
    for (p = head; p; p = p->next) cout << p->data;
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
    slistEl* p = head;

    if (p)
    {
        head = p->next;
        delete p;
    }
}

// Scala dwie obce listy
//----------------------
void slist::merge(slist& l1, slist& l2) {
    slistEl* p;
    push_front(0);
    p = head;

    while (l1.head && l2.head) {
        if (l1.head->data > l2.head->data) {
            p->next = l2.head;
            l2.head = l2.head->next;
        }
        else {
            p->next = l1.head;
            l1.head = l1.head->next;
        }
        p = p->next;
    }

    while (l1.head) {
        p->next = l1.head;
        l1.head = l1.head->next;
        p = p->next;
    }
    while (l2.head) {
        p->next = l2.head;
        l2.head = l2.head->next;
        p = p->next;
    }

    pop_front();
}

//---------------
// Program g³ówny
//---------------

int main()
{
    slist L1, L2, L3; // obiekty list jednokierunkowych
    int c, i;
    char z;

    srand(time(NULL));

    c = 1 + rand() % 2;
    z = 65 + rand() % 26;

    for (i = 0; i < 30; i++)
    {
        L1.push_front(z);
        if (!--c)
        {
            c = 1 + rand() % 2;
            if (z > 'A') z--;
        }
    }

    L1.printl();

    c = 1 + rand() % 2;
    z = 65 + rand() % 26;

    for (i = 0; i < 40; i++)
    {
        L2.push_front(z);
        if (!--c)
        {
            c = 1 + rand() % 2;
            if (z > 'A') z--;
        }
    }
    L2.printl();

    cout << endl;

    L3.merge(L1, L2);
    L3.printl();

    return 0;
}
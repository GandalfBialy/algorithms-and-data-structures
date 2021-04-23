// Wyszukiwanie najwiêkszego elementu
// Data: 18.02.2012
// (C)2020 mgr Jerzy Wa³aszek
//-----------------------------------

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

// Element listy
//--------------
struct dlistEl
{
    dlistEl* next;   // nastêpnik
    dlistEl* prev;   // poprzednik
    char data;
};

// Definicja obiektu listy dwukierunkowej
//---------------------------------------
class dlist
{
public:
    dlistEl* head;  // pocz¹tek listy
    dlistEl* tail;  // koniec listy
    unsigned count;  // licznik elementów

    dlist();         // konstruktor
    ~dlist();        // destruktor
    void printl();
    void push_front(char v);
    void push_back(char v);
    void insert_before(dlistEl* e, char v);
    void insert_after(dlistEl* e, char v);
    void remove(dlistEl* e);
    void pop_front();
    void pop_back();
    dlistEl* max();
};

//------------------------------------
// Metody obiektu listy dwukierunkowej
//------------------------------------

// Inicjuje pola zmiennej listy
//-----------------------------
dlist::dlist()
{
    head = tail = NULL;
    count = 0;
}

// Usuwa listê z pamiêci
//----------------------
dlist::~dlist()
{
    while (count) pop_front();
}

// Wyœwietla zawartoœæ elementów listy
//----------------------------------------------
void dlist::printl()
{
    dlistEl* p;

    cout << setw(3) << count << ": ";
    p = head;
    while (p)
    {
        cout << p->data;
        p = p->next;
    }
    cout << endl;
}

// Dodaje nowy element na pocz¹tek listy
//------------------------------------------------
void dlist::push_front(char v)
{
    dlistEl* p;

    p = new dlistEl;
    p->data = v;
    p->prev = NULL;
    p->next = head;
    head = p;
    count++;
    if (p->next) p->next->prev = p;
    else tail = p;
}

// Dodaje nowy element na koniec listy
//----------------------------------------------
void dlist::push_back(char v)
{
    dlistEl* p;

    p = new dlistEl;
    p->data = v;
    p->next = NULL;
    p->prev = tail;
    tail = p;
    count++;
    if (p->prev) p->prev->next = p;
    else head = p;
}

// Dodaje nowy element przed wybranym
//-----------------------------------
void dlist::insert_before(dlistEl* e, char v)
{
    dlistEl* p;

    if (e == head) push_front(v);
    else
    {
        p = new dlistEl;
        p->data = v;
        p->next = e;
        p->prev = e->prev;
        count++;
        e->prev->next = p;
        e->prev = p;
    }
}

// Dodaje nowy element za wybranym
//--------------------------------
void dlist::insert_after(dlistEl* e, char v)
{
    dlistEl* p;

    if (e == tail) push_back(v);
    else
    {
        p = new dlistEl;
        p->data = v;
        p->next = e->next;
        p->prev = e;
        count++;
        e->next->prev = p;
        e->next = p;
    }
}

// Usuwa wybrany element z listy
//------------------------------
void dlist::remove(dlistEl* e)
{
    count--;
    if (e->prev) e->prev->next = e->next;
    else        head = e->next;
    if (e->next) e->next->prev = e->prev;
    else        tail = e->prev;
    delete e;
}

// Usuwa element z pocz¹tku listy
//-------------------------------
void dlist::pop_front()
{
    if (count) remove(head);
}

// Usuwa element z koñca listy
//----------------------------
void dlist::pop_back()
{
    if (count) remove(tail);
}

// Wyszukuje element o najwiêkszej wartoœci
//-----------------------------------------
dlistEl* dlist::max() {
    dlistEl* p, * pmax;
    pmax = head;

    if (head) {
        for (p = head->next; p; p = p->next) {
            if (p->data > pmax->data) {
                pmax = p;
            }
        }   
    }
        
    return pmax;
}

//---------------
// Program g³ówny
//---------------

int main()
{
    dlist L;
    dlistEl* p;
    int i;

    srand(time(NULL));
    for (i = 0; i < 40; i++) L.push_back(65 + rand() % 26);
    L.printl();
    p = L.max();
    L.insert_before(p, '.');
    L.insert_after(p, '.');
    L.printl();

    return 0;
}
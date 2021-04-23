// Zliczanie elementów listy
// Data: 19.02.2012
// (C)2020 mgr Jerzy Wa³aszek
//---------------------------

#include <iostream>
#include <iomanip>
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
    void     printl();
    void     push_front(char v);
    void     pop_front();
    unsigned countv(char v);
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
    slistEl* p;
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
    slistEl* p = head; // zapamiêtujemy pocz¹tek

    if (p)
    {
        head = p->next;   // nowy pocz¹tek
        delete p;         // usuñ element z pamiêci
    }
}

// Oblicza liczbê elementów zawieraj¹cych v
//-----------------------------------------
unsigned slist::countv(char v) {
    slistEl* p = head;
    unsigned c = 0;

    while (p) {
        if (p->data == v) {
            c++;
        }
        p = p->next;
    }
    return c;
}

int main()
{
    slist L;
    int i;

    srand(time(NULL));

    for (i = 0; i < 400; i++) L.push_front(65 + rand() % 26);
    L.printl();

    for (i = 'A'; i <= 'Z'; i++) cout << char(i) << ": " << setw(3) << L.countv(i) << endl;
    return 0;
}
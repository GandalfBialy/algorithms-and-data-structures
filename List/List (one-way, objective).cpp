#include <iostream>

using namespace std;

struct slistEl {
    slistEl* next;
    char data;
};

class slist {
    public:
        slistEl* head;

        slist();
        ~slist();
        unsigned size();
        void printl();
        void push_front(char v);
        void push_back(char v);
        void insert_before(slistEl* e, char v);
        void insert_after(slistEl* e, char v);
        void pop_front();
        void pop_back();
        void remove(slistEl* e);
};

slist::slist() {
    head = NULL;
}

slist::~slist() {
    while (head) {
        pop_front();
    }
}

unsigned slist::size() {
    unsigned c = 0;
    slistEl* p = head;
    while (p) {
        c++;
        p = p->next;
    }
    return c;
}

void slist::printl() {
    unsigned i;
    slistEl* p = head;

    cout << "Number of elements : " << size() << endl;
    for (i = 1; p; p = p->next) {
        cout << "Element #" << i++ << "  data = " << p->data << endl;
    }
    cout << endl;
}

void slist::push_front(char v) {
    slistEl* p;

    p = new slistEl;
    p->next = head;
    p->data = v;
    head = p;
}

void slist::push_back(char v) {
    slistEl* p, * e;

    e = new slistEl;  // stworzenie nowego element
    e->next = NULL;   // inicjalizacja elementu
    e->data = v;
    p = head;
    if (p) {
        while (p->next) {
            p = p->next;
        }
        p->next = e;
    }
    else {
        head = e;
    }
}

void slist::insert_before(slistEl* e, char v) {
    slistEl* p = head;

    if (p == e) {
        push_front(v);
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

void slist::insert_after(slistEl* e, char v) {
    slistEl* p = new slistEl;

    p->next = e->next;
    p->data = v;
    e->next = p;
}

void slist::pop_front() {
    slistEl* p = head;

    if (p) {
        head = p->next;
        delete p;
    }
}

void slist::pop_back() {
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

void slist::remove(slistEl* e) {
    slistEl* p;

    if (head == e) {
        pop_front();
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

int main()
{
    slist L;
    slistEl* e;
    char i;

    for (i = 'A'; i <= 'G'; i++) {
        L.push_back(i);
    }
    L.printl();

    e = L.head;
    for (i = 'A'; i <= 'C'; i++) {
        e = e->next;
    }

    L.insert_before(e, '+');
    L.insert_after(e, '*');
    L.printl();

    L.remove(e);
    L.pop_front();
    L.pop_back();
    L.printl();
}
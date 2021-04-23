#include <iostream>
#include <cstdlib>
#include <ctime>

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
    void printl();
    void push_front(char v);
    void pop_front();
    slistEl* find_first(char v);
    slistEl* find_second(char v);
};

slist::slist() {
    head = NULL;
}

slist::~slist() {
    while (head) {
        pop_front();
    }
}

void slist::printl() {
    for (slistEl* p = head; p; p = p->next) {
        cout << p->data << " ";
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

void slist::pop_front() {
    slistEl* p = head;

    if (p) {
        head = p->next;
        delete p;
    }
}

slistEl* slist::find_first(char v) {
    slistEl* p = head;
    while (p && p->data != v) {
        p = p->next;
    }
    return p;
}

slistEl* slist::find_second(char v) {
    slistEl* p = head;
    while (p && p->data != v) {
        p = p->next;
    }
    if (p) {
        p = p->next;
    }
    while (p && p->data != v) {
        p = p->next;
    }
    return p;
}

int main()
{
    slist L;
    slistEl* p;
    int i;

    srand(time(NULL));

    for (i = 0; i < 20; i++) {
        L.push_front(65 + rand() % 7);
    }
    L.printl();

    /*do {
        p = L.find_first('A');
        if (p) {
            p->data = '.';
            L.printl();
        }
    } while (p);*/

    do {
        p = L.find_second('B');
        if (p) {
            p->data = '.';
            L.printl();
        }
    } while (p);

    return 0;
}
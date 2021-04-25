#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

struct slistEl {
    slistEl* next;
    string data;
};

unsigned int hf(string s) {
    unsigned int h = 0;

    for (int i = 0; i < s.length(); i++) {
        h = 31 * h + s[i] - 65;
    }
        
    return h % 10;
}

int main()
{
    slistEl* T[10], * p, * r;
    unsigned int h, c;
    string s;
    bool t;

    srand(time(NULL));

    for (int i = 0; i < 10; i++) {
        T[i] = NULL;
    }

    for (int i = 0; i < 35; i++) {
        s = "";
        for (int j = 0; j < 4; j++) {
            s += 65 + (rand() % 26);
        }

        h = hf(s);
        p = T[h];
        t = true;

        if (p) {
            while (true) {
                if (p->data == s) {
                    t = false;
                    break;
                }
                if (!p->next) {
                    break;
                }
                p = p->next;
            }
        }
            

        if (t) {
            r = new slistEl;
            r->data = s;
            r->next = NULL;
            if (!p) {
                T[h] = r;
            }
            else {
                p->next = r;
            }
        }
    }

    for (int i = 0; i < 10; i++) {
        cout << "T [ " << i << " ] = ";
        p = T[i];
        while (p) {
            cout << p->data << " ";
            p = p->next;
        }
        cout << endl;
    }
    cout << endl;

    s = "AAAA";

    do {
        h = hf(s);
        c = 0;
        p = T[h];
        while (p && (p->data != s)) {
            c++;
            p = p->next;
        }

        if (p) {
            cout << s << " hf = " << h << " c = " << c << endl;
        }

        for (int i = 4; i > 0; i--) {
            s[i - 1] = s[i - 1] + 1;
            if (s[i - 1] <= 'Z') {
                break;
            }
            s[i - 1] = 'A';
        }
    } while (s != "AAAA");

    for (int i = 0; i < 10; i++) {
        while ((p = T[i])) {
            T[i] = p->next;
            p->data = "";
            delete p;
        }
    }
    cout << endl;

    return 0;
}
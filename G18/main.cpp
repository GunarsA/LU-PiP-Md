// PS > g++ main.cpp; .\a.exe

// Izveidot divas programmas valodā C++, kas strādā ar vērtību virkni divos dažādos veidos:
//   1) to realizējot kā vienvirziena saistīto sarakstu, izmantojot dinamiskas datu struktūras,
//   2) izmantojot STL::list konteineru.
// Abās realizācijās ir jāizveido prasītā specifiskā vērtību virknes apstrādes
// funkcija un jānodemonstrē tā darbībā, cita starpā parādot gan sākotnējās,
// gan rezultējošās vērtības. Saistītā saraksta gadījumā jāuzraksta arī
// nepieciešamās palīgfunkcijas (piemēram, elementu pievienošanai), kā arī pēc
// tā izmantošanas korekti jāatbrīvo izdalītā atmiņa.

// G18. Uzrakstīt funkciju, kas izmet no saraksta tos elementus, kuriem vērtība
// vienāda ar to kārtas numuru.

// Gunārs Ābeltiņš
// 2023-03-20

#include <windows.h>
#include <iostream>
#include <list>

using namespace std;

template <typename T>
class SingleLinkedList
{
    struct node
    {
        T value;
        node *next;
    };

public:
    node *first = NULL;
    node *last = NULL;

    SingleLinkedList()
    {
        cout << "Saraksts inicializēts!" << endl;
    }

    ~SingleLinkedList()
    {
        for (auto i = first; i; i = first)
        {
            first = first->next;
            delete i;
        }

        cout << "Saraksts izdzēsts!" << endl;
    }

    void push_back(T value)
    {
        node *newNode = new node{value, nullptr};

        if (!first)
        {
            first = last = newNode;
        }
        else
        {
            last->next = newNode;
            last = last->next;
        }
    }
};

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    int go;
    do
    {
        cout << "Ievadiet elementu skaitu: ";
        int len;
        cin >> len;

        list<int> list;
        SingleLinkedList<int> customList;

        cout << "Ievadiet [" << len << "] elementu(s): ";
        for (int i = 0; i < len; ++i)
        {
            int temp;
            cin >> temp;
            list.push_back(temp);
            customList.push_back(temp);
        }

        int pos = 1;
        for (auto i = list.begin(); i != list.end(); ++pos)
            if (*i == pos)
                i = list.erase(i);
            else
                ++i;
        cout << "Saraksta elementi pēc pārveidojuma: ";
        for (auto &i : list)
        {
            cout << i << " ";
        }
        cout << endl;

        for (pos = 1; customList.first && customList.first->value == pos; ++pos)
        {
            auto *p = customList.first;
            customList.first = customList.first->next;
            delete p;

            if (!customList.first)
                customList.last = customList.first;
        }
        ++pos;
        if (customList.first && customList.first->next)
        {
            for (auto *prev = customList.first, *i = prev->next; i; prev = i, i = i->next, ++pos)
            {
                while (i && i->value == pos)
                {
                    prev->next = i->next;
                    delete i;
                    i = prev->next;

                    ++pos;

                    if (!i)
                    {
                        customList.last = prev;
                        break;
                    }
                }
            }
        }
        cout << "Paštaisītā saraksta elementi pēc pārveidojumiem: ";
        for (auto &i = customList.first; i; i = i->next)
        {
            cout << i->value << " ";
        }
        cout << endl;

        cout << "Atkārtot? (1 | 0): ";
        cin >> go;
    } while (go);

    return 0;
}

//        Ievads | Izvads
// --------------|--------------------
//             3 | 
//         1 2 3 |
// --------------|--------------------
//             4 | 2 5
//       2 2 3 5 | 2 5
// --------------|--------------------
//             0 | 
// --------------|--------------------
//             5 | 5 4 2 1
//     5 4 3 2 1 | 5 4 2 1


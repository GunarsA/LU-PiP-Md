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

#include <windows.h>
#include <iostream>
#include <list>

using namespace std;

struct node
{
    int value;
    node *next;
};

class SingleLinkedList
{
public:
    node *first = NULL;
    node *last = NULL;

    SingleLinkedList()
    {
        cout << "List initialized!" << endl;
    }

    ~SingleLinkedList()
    {
        for (auto i = first; i; i = first)
        {
            first = first->next;
            delete i;
        }

        cout << "List deleted!" << endl;
    }

    void push_back(int value)
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

    list<int> list;
    
    cout << "Ievadiet elementus: ";

    string input;
    int element;
    getline(cin, input);
    for(int i = 2; !input.empty(); ++i)
    {
        int temp = stoi(input);
        list.push_back(temp);
        getline(cin, input);
    }

    int pos = 1;
    for(auto i = list.begin(); i != list.end(); ++i, ++pos)
        if(*i == pos) i = list.erase(i);
    
    cout << "Saraksta elementi pēc parveidojuma: ";
    for(auto &i : list){
        cout << i << " ";
    }
    cout << endl;

    return 0;
}
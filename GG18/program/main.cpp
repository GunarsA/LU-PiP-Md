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

#include "header.hpp"
#include "program.cpp"

using namespace std;

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    int go;
    do
    {
        list<int> list;
        SingleLinkedList<int> customList;

        cout << "Ievadiet elementu(s) (Ievadi pabeidz ar CTRL+Z): ";
        for (int value; cin >> value;)
        {
            list.push_back(value);
            customList.push_back(value);
        }
        cin.clear();
        cin.ignore(INT_MAX, '\n');

        eraseIndex(list);
        cout << "Saraksta elementi pēc pārveidojuma: ";
        printList(list);

        eraseIndex(customList);
        cout << "Paštaisītā saraksta elementi pēc pārveidojumiem: ";
        printList(customList);

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

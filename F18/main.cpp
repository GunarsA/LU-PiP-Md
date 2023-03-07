// PS > g++ main.cpp; .\a.exe

// Izveidot programmu valodā C++, kas apstrādā teksta failu secīgā režīmā. Dati
// no faila jānolasa pa vienai rindiņai. Nedrīkst dublēt visa faila saturu
// operatīvajā atmiņā. Sīkākas prasības sk. Laboratorijas darbu noteikumos.

// F18. Izvadīt failā dotajā teksta failā  f sastapto vārdu sadalījumu pēc
// garuma (Tas ir, cik vienburtīgu, cik divburtīgu, utt. vārdu ir failā). Par
// vārdu uzskatīt patvaļīgu simbolu virkni, kas atdalīta ar tukšumiem vai
// pieturas zīmēm (punkts, komats, apaļās iekavas, izsaukuma zīme, jautājuma zīme).

// Gunārs Ābeltiņš
// 2023.03.06

#include <windows.h>
#include <iostream>
#include <fstream>
#include <algorithm>

#define uint unsigned int
#define MAX_WORD_SIZE (uint)100

using namespace std;

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    const char SEPARATORS[] = {' ', '.', ',', '(', ')', '!', '?'};

    int go = 0;
    do
    {
        uint wordCount[MAX_WORD_SIZE]{};

        ifstream fileIn("f.txt", ios::in);

        if (!fileIn.is_open())
        {
            cout << "Fails 'f.txt' neeksistē!" << endl;
        }
        else
        {
            uint longestWord = 0;

            while (!fileIn.eof())
            {
                string line;
                getline(fileIn, line);
                line.push_back(' ');

                for (uint i = 0, wordLen = 0; i < line.size(); ++i, ++wordLen)
                {
                    // Pārbauda vai ir atrast vārdus atdalošs simbols
                    if (find(begin(SEPARATORS), end(SEPARATORS), line[i]) != end(SEPARATORS))
                    {
                        // Ja pa vidu simboliem bija vārds, kas garāks par 0,
                        // tad saglabā tā garumu
                        if (wordLen)
                        {
                            ++wordCount[wordLen - 1];
                            // Saglābā garākā vārda garumu, lai beigās netiktu izvadītas daudzas nulles.
                            longestWord = max(longestWord, wordLen);
                        }
                        wordLen = -1;
                    }
                }
            }
            fileIn.close();

            ofstream fileOut("out.txt", ios::out);
            for (uint i = 0; i < min(longestWord, MAX_WORD_SIZE); ++i)
            {
                // Saglabā izvades rindu simbolu virknē, lai nebūtu koda duplikācija.
                string outputStr = "Vārdi garumā [" + to_string(i + 1) + "]: " + to_string(wordCount[i]) + "\n";
                cout << outputStr;
                fileOut << outputStr;
            }
            fileOut.close();
        }
        cout << "Atkārtot? (1 | 0)?: ";
        cin >> go;
    } while (go);

    return 0;
}

//                                          Ievads | Izvads
// ------------------------------------------------|--------------------
// Dolore, minim commodo () do aliqua cupidatat.!? | Vārdi garumā [1]: 0
//                                                 | Vārdi garumā [2]: 1
//                                                 | Vārdi garumā [3]: 0
//                                                 | Vārdi garumā [4]: 0
//                                                 | Vārdi garumā [5]: 1
//                                                 | Vārdi garumā [6]: 2
//                                                 | Vārdi garumā [7]: 1
//                                                 | Vārdi garumā [8]: 0
//                                                 | Vārdi garumā [9]: 1
// ------------------------------------------------|--------------------
//                                                 |
// ------------------------------------------------|--------------------
// a b c ee ef                                     | Vārdi garumā [1]: 3
//                                                 | Vārdi garumā [2]: 2


// PS > g++ main.cpp; .\a.exe

// Izveidot programmu valodā C++, kas apstrādā teksta failu secīgā režīmā. Dati
// no faila jānolasa pa vienai rindiņai. Nedrīkst dublēt visa faila saturu
// operatīvajā atmiņā. Sīkākas prasības sk. Laboratorijas darbu noteikumos.

// F18. Izvadīt failā dotajā teksta failā  f sastapto vārdu sadalījumu pēc
// garuma (Tas ir, cik vienburtīgu, cik divburtīgu, utt. vārdu ir failā). Par
// vārdu uzskatīt patvaļīgu simbolu virkni, kas atdalīta ar tukšumiem vai
// pieturas zīmēm (punkts, komats, apaļās iekavas, izsaukuma zīme, jautājuma zīme).

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

    uint wordCount[MAX_WORD_SIZE]{};
    char separators[] = {' ', '.', ',', '(', ')', '!', '?'};

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
                if (find(begin(separators), end(separators), line[i]) != end(separators))
                {
                    if (wordLen)
                    {
                        ++wordCount[wordLen - 1];
                        longestWord = max(longestWord, wordLen);
                    }
                    wordLen = -1;
                }
            }
        }

        for (uint i = 0; i < min(longestWord, MAX_WORD_SIZE); ++i)
        {
            cout << "Vārdi garumā [" << i + 1 << "]: " << wordCount[i] << endl;
        }
    }

    return 0;
}

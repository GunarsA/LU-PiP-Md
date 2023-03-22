// Izveidot programmu valodā C++.  Ar faila komponenti tiek saprasts fiksēta
// garuma ieraksts. Sīkākās prasības sk. Laboratorijas darbu noteikumos.

// H13. Doti divi bināri faili f1 un f2, kuru komponentes ir ieraksti ar
// struktūru: atslēga (int), vārds (nepārsniedz 30 simbolus). Failu
// komponentes sakārtotas atslēgu pieaugšanas secībā. Uzrakstīt programmu,
// kas apvieno failus f1 un f2 failā f3  tā, lai arī f3 komponentes būtu
// atslēgu pieaugšanas secībā (failos  nedrīkst parādīties divas komponentes
// ar vienādu atslēgu vērtību). Uzrakstīt arī palīgprogrammas, kas ļauj
// izveidot failus f1 un f2 un izdrukā failu saturu.

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct struc
{
    int key;
    char value[31];
};

void createFile(string fileName)
{
    vector<struc> vec;
    cout << "Ievadi vertības (beigas spied CTRL+Z): ";

    struc temp;
    while (cin >> temp.key && cin >> temp.value)
    {
        vec.push_back(temp);
    }

    ofstream fileOut(fileName, ios::out | ios::binary);
    fileOut.write((char *)&vec[0], vec.size() * sizeof(struc));
}

void readFile(string fileName)
{
    vector<struc> vec;
    ifstream fileIn(fileName, ios::in | ios::binary);

    if (fileIn.is_open())
    {
        while (true)
        {
            struc temp;
            fileIn.read((char *)&temp, sizeof(struc));

            if (fileIn.eof())
                break;

            vec.push_back(temp);
        }
    }

    for (auto &i : vec)
    {
        cout << i.key << " " << i.value << endl;
    }
}

int main()
{
    createFile("f1.bin");
    readFile("f1.bin");
}
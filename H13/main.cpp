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
#include <tuple>

#define MAX_LEN 30

using namespace std;

struct struc
{
    int key;
    string value;

    friend bool operator<(const struc &lhs, const struc &rhs)
    {
        return tie(lhs.key, lhs.value) < tie(rhs.key, rhs.value);
    }

    friend bool operator>(const struc &lhs, const struc &rhs)
    {
        return tie(lhs.key, lhs.value) > tie(rhs.key, rhs.value);
    }
};

template <typename T>
int partition(T arr[], int low, int high)
{
    T pivot = arr[low];
    int i = low - 1, j = high + 1;

    while (true)
    {
        do
        {
            ++i;
        } while (arr[i] < pivot);

        do
        {
            --j;
        } while (arr[j] > pivot);

        if (i >= j)
        {
            return j;
        }

        swap(arr[i], arr[j]);
    }
}

template <typename T>
void quickSort(T arr[], int low, int high)
{
    if (low < high)
    {
        int pivot = partition(arr, low, high);

        quickSort(arr, low, pivot);
        quickSort(arr, pivot + 1, high);
    }
}

void writeFile(string fileName)
{
    vector<struc> vec;
    cout << "Ievadi vertības (beigas spied CTRL+Z): ";

    struc temp;
    while (cin >> temp.key && cin >> temp.value)
    {
        temp.value.resize(MAX_LEN + 1);
        vec.push_back(temp);
    }

    if (vec.size())
    {
        quickSort(vec.data(), 0, vec.size() - 1);

        ofstream fileOut(fileName, ios::out | ios::binary);

        for (auto &i : vec)
        {
            fileOut.write((char *)&i.key, sizeof(int));
            fileOut.write((char *)&i.value.c_str()[0], MAX_LEN + 1);
        }
    }
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
            temp.value.resize(MAX_LEN + 1);

            fileIn.read((char *)&temp.key, sizeof(int));
            fileIn.read((char *)&temp.value.c_str()[0], MAX_LEN + 1);

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
    writeFile("f1.bin");
    readFile("f1.bin");
}
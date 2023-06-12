#include <iostream>
using namespace std;

class Persona
{
private:
    string uzvards;
    string vards;
    string personaskods;

public:
    Persona(string uzvards, string vards, string personaskods)
    {
        this->uzvards = uzvards;
        this->vards = vards;
        this->personaskods = personaskods;
    }
    ~Persona()
    {
        cout << "Objekts ir likvidēts!" << endl;
    }
    void print()
    {
        cout << "Uzvārds: " << uzvards << endl;
        cout << "Vārds: " << vards << endl;
        cout << "Personas kods: " << personaskods << endl;
    }
};

class Skolnieks : public Persona
{
private:
    int skoluskaits;
    string *skolas;

public:
    Skolnieks(string uzv, string var, string pk, int sksk, string skol[]) : Persona(uzv, var, pk)
    {
        skoluskaits = sksk;
        skolas = new string[skoluskaits];
        for (int i = 0; i < skoluskaits; i++)
        {
            skolas[i] = skol[i];
        }
    }
    ~Skolnieks()
    {
        delete[] skolas;
        cout << "Atmiņa atbrīvota!" << endl;
    }
    void print()
    {
        Persona::print();
        cout << "Skolu skaits: " << skoluskaits << endl;
        cout << "Skolas: ";
        for (int i = 0; i < skoluskaits; i++)
        {
            cout << skolas[i] << " ";
        }
        cout << endl;
    }
};

int main()
{
    Persona p("Berzins", "Janis", "123456-12345");
    p.print();
    string skolas[2] = {"RTU", "LU"};
    Skolnieks s("Juris", "Upnieks", "222222-12345", 2, skolas);
    s.print();

    return 0;
}
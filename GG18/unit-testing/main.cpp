// PS > g++ main.cpp; a.exe

#include <iostream>
#include <list>

#include "../program/program.cpp"

using namespace std;

void test1()
{
    list<int> lis = {2, 2, 3, 5};

    eraseIndex(lis);

    cout << (lis == list<int>{2, 5}) << endl;
}

void test2()
{
    SingleLinkedList<int> customList;

    int arr[] = {2, 2, 3, 5};
    for (auto &i : arr)
        customList.push_back(i);

    eraseIndex(customList);

    int arr2[] = {2, 5};
    int i = 0;
    for (auto *curr = customList.first; curr; curr = curr->next, ++i)
    {
        if (i == sizeof(arr2) / sizeof(int) || arr2[i] != curr->value)
        {
            cout << 0 << endl;
            return;
        }
    }

    cout << 1 << endl;
}

void test3()
{
}

int main()
{
    test1();
    test2();
    test3();

    return 0;
}
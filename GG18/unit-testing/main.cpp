// PS > g++ main.cpp; a.exe

// Gunārs Ābeltiņš
// 2023-05-23

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
    int len = 0;
    for (auto *curr = customList.first; curr; curr = curr->next, ++i, ++len)
    {
        if (i == sizeof(arr2) / sizeof(int) || arr2[i] != curr->value)
        {
            cout << 0 << endl;
            return;
        }
    }

    if (len != sizeof(arr2) / sizeof(int))
        cout << 0 << endl;
    else
        cout << 1 << endl;
}

void test3()
{
    SingleLinkedList<int> customList;
    int arr[] = {1, 2, 3};
    for (auto &i : arr)
        customList.push_back(i);

    eraseIndex(customList);

    int arr2[] = {};
    int i = 0;
    int len = 0;
    for (auto *curr = customList.first; curr; curr = curr->next, ++i, ++len)
    {
        if (i == sizeof(arr2) / sizeof(int) || arr2[i] != curr->value)
        {
            cout << 0 << endl;
            return;
        }
    }
    
    if (len != sizeof(arr2) / sizeof(int))
        cout << 0 << endl;
    else
        cout << 1 << endl;
}

void test4()
{
    SingleLinkedList<int> customList;
    int arr[] = {1, 2, 4};
    for (auto &i : arr)
        customList.push_back(i);

    eraseIndex(customList);

    int arr2[] = {4};
    int i = 0;
    int len = 0;
    for (auto *curr = customList.first; curr; curr = curr->next, ++i, ++len)
    {
        if (i == sizeof(arr2) / sizeof(int) || arr2[i] != curr->value)
        {
            cout << 0 << endl;
            return;
        }
    }
    
    if (len != sizeof(arr2) / sizeof(int))
        cout << 0 << endl;
    else
        cout << 1 << endl;
}

void test5()
{
    SingleLinkedList<int> customList;

    try
    {
        eraseIndex(customList);
    }
    catch (std::runtime_error &e)
    {
        if (e.what() == std::string("List is empty"))
            cout << 1 << endl;
        else
            cout << 0 << endl;
        return;
    }
    cout << 0 << endl;
}

int main()
{
    test1();
    test2();
    test3();
    test4();
    test5();

    return 0;
}
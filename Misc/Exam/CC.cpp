#include <iostream>

using namespace std;

struct Node
{
    int info;
    Node *next;
};

int SeqLenOld(Node const *listHead1, Node const *listHead2)
{
    bool found = false;
    auto solve = [&](auto &&solve, Node const *listHead1, Node const *listHead2) -> int
    {
        if (listHead1 == nullptr || listHead2 == nullptr)
            return 0;

        if (listHead1->info == listHead2->info)
        {
            int ans = solve(solve, listHead1->next, listHead2->next);
            if (found)
                return ans;
            found = true;
            return listHead1->info;
        }

        if (listHead1->info < listHead2->info)
        {
            int ans = solve(solve, listHead1, listHead2->next);
            if (found)
                return ans;
            if (listHead1->info == ans + 1)
                return ans + 1;
            found = true;
            return ans;
        }
        else
        {
            int ans = solve(solve, listHead1->next, listHead2);
            if (found)
                return ans;
            if (listHead2->info == ans + 1)
                return ans + 1;
            found = true;
            return ans;
        }
    };
    int ans = solve(solve, listHead1, listHead2);
    if (found)
        return ans;
    if (listHead1 && listHead1->info == ans + 1 || listHead2 && listHead2->info == ans + 1)
        return ans + 1;
    return ans;
}

int SeqLen(Node const *listHead1, Node const *listHead2)
{
    int ans = 0;
    for (; listHead1 && ans < listHead1->info ||
           listHead2 && ans < listHead2->info;
         ++ans)
    {
        bool found = false;
        for (auto i = listHead1; i != nullptr; i = i->next)
        {
            if (i->info == ans + 1)
            {
                found = true;
                break;
            }
        }
        for (auto i = listHead2; i != nullptr; i = i->next)
        {
            if (i->info == ans + 1)
            {
                if (found)
                    return ans + 1;
                found = true;
                break;
            }
        }
        if (!found)
            return ans;
    }
    return ans;
}

int main()
{
    int arr[] = {4, 3, 2, 2};
    Node *listHead1 = new Node{4, new Node{3, new Node{2, new Node{1, nullptr}}}};
    int arr2[] = {3};
    Node *listHead2 = new Node{1, nullptr};

    cout << SeqLen(nullptr, listHead1) << endl;
    return 0;
}
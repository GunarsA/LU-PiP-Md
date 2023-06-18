#include <iostream>
#include <list>
#include <map>

using namespace std;

int remove2DistinctOddsEvens(list<int> &List)
{
    map<int, int> Map;
    int odd_cnt = 0, even_cnt = 0;
    auto it = List.begin();

    while (it != List.end())
    {
        if (Map.find(*it) != Map.end())
        {
            Map[*it]++;
            ++it;
        }
        else if (*it % 2 == 1 && odd_cnt < 2)
        {
            Map[*it] = 0;
            it = List.erase(it);
            odd_cnt++;
        }
        else if (*it % 2 == 0 && even_cnt < 2)
        {
            Map[*it] = 0;
            it = List.erase(it);
            even_cnt++;
        }
        else
        {
            ++it;
        }
    }

    int ans = 0;
    for (auto &i : Map)
        ans += i.second;

    return ans;
}

int main()
{
    list<int> List = {1, 2, 1, 3, 2, 4, 5, 2};
    cout << remove2DistinctOddsEvens(List) << endl;
    for (auto &i : List)
        cout << i << " ";
    cout << endl;
    return 0;
}
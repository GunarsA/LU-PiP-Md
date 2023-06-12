#include <iostream>

using namespace std;

int main()
{
    (void)!freopen("team.in", "w", stdout);

    int n = 10000;
    cout << "1 2 0\n";
    for(int i = 2; i < n; ++i){
        cout << i << " " << i + 1 << " 0\n";
    }
    cout << n << " 0 0\n";
    cout << "0 0 0\n";
}
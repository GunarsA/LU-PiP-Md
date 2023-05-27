#include <iostream>

using namespace std;

int main()
{
    (void)!freopen("team.in", "w", stdout);

    cout << "1 2 0\n";
    for(int i = 2; i <= 10000; ++i){
        cout << i << " " << i + 1 << " 0\n";
    }
    cout << "0 0 0\n";
}
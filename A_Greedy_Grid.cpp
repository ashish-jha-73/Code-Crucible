#include <iostream>
using namespace std;
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        cout << (n >= 2 && m >= 2 && (n >= 3 || m >= 3) ? "YES\n" : "NO\n");
    }
}

// AJ
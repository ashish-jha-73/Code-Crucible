#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> defeated_by(n + 1, 0);
    set<int> active;

    for (int i = 1; i <= n; ++i)
        active.insert(i);  // initially all knights are active

    while (m--) {
        int l, r, x;
        cin >> l >> r >> x;

        auto it = active.lower_bound(l);
        vector<int> to_erase;

        while (it != active.end() && *it <= r) {
            if (*it != x) {
                defeated_by[*it] = x;
                to_erase.push_back(*it);
            }
            ++it;
        }

        for (int knight : to_erase)
            active.erase(knight);
    }

    for (int i = 1; i <= n; ++i)
        cout << defeated_by[i] << " ";
    cout << "\n";
    return 0;
}

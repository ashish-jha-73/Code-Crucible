#include <bits/stdc++.h>
using namespace std;

using ll = long long;
set<ll> special; // store all valid palindrome special numbers

// Check if the digit count is valid (digit d must appear exactly d times)
bool isValid(const vector<int>& chosen) {
    for (int d = 1; d <= 9; ++d) {
        if (chosen[d] && chosen[d] != d) return false;
    }
    return true;
}

// Generate all unique palindromic permutations from the digit multiset
void generatePalindromes(const vector<int>& digitCount) {
    vector<char> half;
    char mid = 0;
    for (int d = 1; d <= 9; ++d) {
        if (digitCount[d] % 2 == 1) {
            if (mid != 0) return; // More than 1 odd digit count, can't make palindrome
            mid = '0' + d;
        }
        for (int i = 0; i < digitCount[d] / 2; ++i)
            half.push_back('0' + d);
    }
    if (half.size() > 8) return; 
    sort(half.begin(), half.end());
    set<string> used;
    do {
        string left(half.begin(), half.end());
        string right = left;
        reverse(right.begin(), right.end());
        string full = left + (mid ? string(1, mid) : "") + right;
        if (full[0] != '0') {
            ll num = stoll(full);
            if (num <= 1e17) special.insert(num);
        }
    } while (next_permutation(half.begin(), half.end()));
}

void precompute() {
    for (int mask = 1; mask < (1 << 9); ++mask) {
        vector<int> digitCount(10, 0);
        for (int i = 0; i < 9; ++i) {
            if (mask & (1 << i)) {
                digitCount[i + 1] = i + 1;
            }
        }
        if (isValid(digitCount)) {
            generatePalindromes(digitCount);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    precompute(); // generate all palindrome special numbers
    vector<ll> specialList(special.begin(), special.end());

    int T;
    cin >> T;
    while (T--) {
        string s;
        cin >> s;
        ll N = stoll(s);
        // Binary search for first special palindrome > N
        auto it = upper_bound(specialList.begin(), specialList.end(), N);
        if (it != specialList.end()) {
            cout << *it << '\n';
        } else {
            cout << "-1\n"; // no such number
        }
    }

    return 0;
}

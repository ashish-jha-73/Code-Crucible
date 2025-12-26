#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAX_K = 100;
const int L = 10;  // we split indices into groups of size L (using base L)

ll x[MAX_K + 1];   // 1-indexed

// precompute the numbers for k = 1..MAX_K
// x[i] = 2^{a} * 3^{b} * 5^{c} where
// a = floor((i-1)/L), b = floor((MAX_K - i)/L), c = (i-1)%L
void precompute() {
    // precompute powers of 2,3,5 up to 10 (since L=10)
    ll pow2[11], pow3[11], pow5[11];
    pow2[0] = pow3[0] = pow5[0] = 1;
    for (int i = 1; i <= 10; ++i) {
        pow2[i] = pow2[i-1] * 2;
        pow3[i] = pow3[i-1] * 3;
        pow5[i] = pow5[i-1] * 5;
    }

    for (int i = 1; i <= MAX_K; ++i) {
        int a = (i-1) / L;
        int b = (MAX_K - i) / L;   // because we use k = MAX_K for precomputation
        int c = (i-1) % L;
        x[i] = pow2[a] * pow3[b] * pow5[c];
        // all numbers are within 1e18 by construction
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    precompute();

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        // find smallest k such that k(k+1)/2 >= n-1
        int k = 1;
        while (k * (k+1) / 2 < n-1) {
            ++k;
        }

        // build sequence of indices (1-based)
        vector<int> indices;
        // initial part: self-loops and consecutive edges
        for (int i = 1; i <= k; ++i) {
            indices.push_back(i);
            indices.push_back(i);
        }
        // now indices has size 2k

        if (n <= 2*k) {
            indices.resize(n);
        } else {
            // add cross edges until we have n indices
            int L_idx = 1, R_idx = k;
            // currently last vertex is k
            while ((int)indices.size() < n) {
                // add L_idx
                indices.push_back(L_idx);
                if ((int)indices.size() == n) break;
                // add R_idx-1
                indices.push_back(R_idx - 1);
                ++L_idx;
                --R_idx;
            }
        }

        // output the sequence
        for (int i = 0; i < n; ++i) {
            cout << x[indices[i]] << (i+1==n ? '\n' : ' ');
        }
    }

    return 0;
}
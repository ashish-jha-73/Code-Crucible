#include <bits/stdc++.h>
using namespace std;

class segment_tree {
    private:
    std::vector<int> seg;
    int N;
    void buildTree(int i, int l, int r, std::vector<int> &arr) {
        if (l == r) {
            seg[i] = arr[l];
            return;
        }

        int mid = l + (r - l) / 2;
        buildTree(2*i+1, l, mid, arr);
        buildTree(2*i+2, mid + 1, r, arr);
        seg[i] = seg[2*i+1] + seg[2*i+2];
    }
    void updateTree(int i, int l, int r, int pos, int val) {
        if (l == r) {
            seg[i] = val;
            return;
        }

        int mid = l + (r - l) / 2;
        if (pos <= mid) {
            updateTree(2*i+1, l, mid, pos, val);
        } else {
            updateTree(2*i+2, mid + 1, r, pos, val);
        }

        seg[i] = seg[2*i+1] + seg[2*i+2];
    }
    int queryTree(int i, int l, int r, int ql, int qr) {
        if (r <= qr and l >= ql) {
            return seg[i];
        }
        if (r < ql || l > qr) {
            return 0;
        }

        int mid = l + (r - l) / 2;
        return queryTree(2*i+1, l, mid, ql, qr) + queryTree(2*i+2, mid + 1, r, ql, qr);
    }
    public:
    segment_tree(std::vector<int> &arr) {
        this->N = arr.size();
        seg.resize(4*N);
        buildTree(0, 0, N - 1, arr);
    }
    void update(int pos, int val) {
        if (pos < 0 || pos >= N) return;
        updateTree(0, 0, N - 1, pos, val);
    }
    int query(int ql, int qr) {
        if (ql > qr || ql < 0 || qr >= N) return 0;
        return queryTree(0, 0, N - 1, ql, qr);
    }
};

int main() {
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    const int TESTS = 100;
    const int MAX_N = 100;
    const int MAX_VAL = 1000;

    for (int test = 1; test <= TESTS; ++test) {
        int n = rng() % MAX_N + 1;
        vector<int> arr(n);
        for (int& x : arr)
            x = rng() % MAX_VAL;

        // Prefix sum
        vector<long long> pref(n + 1, 0);
        for (int i = 0; i < n; ++i)
            pref[i + 1] = pref[i] + arr[i];

        // Segment tree
        segment_tree seg(arr);

        // Random queries
        for (int q = 0; q < 50; ++q) {
            int l = rng() % n;
            int r = rng() % n;
            if (l > r) swap(l, r);

            long long expected = pref[r + 1] - pref[l];
            long long actual = seg.query(l, r);

            if (expected != actual) {
                cout << "❌ Test failed!\n";
                cout << "Array: ";
                for (int v : arr) cout << v << " ";
                cout << "\nQuery: [" << l << ", " << r << "]\n";
                cout << "Expected: " << expected << ", Got: " << actual << "\n";
                return 1;
            }
        }

        // Random updates
        for (int u = 0; u < 20; ++u) {
            int idx = rng() % n;
            int val = rng() % MAX_VAL;
            arr[idx] = val;
            seg.update(idx, val);

            // Recompute prefix sum
            for (int i = 0; i < n; ++i)
                pref[i + 1] = pref[i] + arr[i];

            for (int q = 0; q < 10; ++q) {
                int l = rng() % n;
                int r = rng() % n;
                if (l > r) swap(l, r);

                long long expected = pref[r + 1] - pref[l];
                long long actual = seg.query(l, r);

                if (expected != actual) {
                    cout << "❌ Test failed after update!\n";
                    cout << "Array: ";
                    for (int v : arr) cout << v << " ";
                    cout << "\nQuery: [" << l << ", " << r << "]\n";
                    cout << "Expected: " << expected << ", Got: " << actual << "\n";
                    return 1;
                }
            }
        }
    }

    cout << "✅ All tests passed successfully!\n";
    return 0;
}
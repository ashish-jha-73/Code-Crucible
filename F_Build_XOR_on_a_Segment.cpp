#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;


const int MAX_VAL = 4096;
const int MAX_K = 13;    
const int MAX_N = 10005; 
const int MAX_Q = 1000005;


int dp[MAX_K][MAX_VAL];
int a[MAX_N];
int ans[MAX_Q];

vector<tuple<int, int, int>> queries[MAX_N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int l, r, x;
        cin >> l >> r >> x;
        queries[r].emplace_back(l, x, i);
    }

    for (int k = 0; k < MAX_K; ++k) {
        for (int v = 0; v < MAX_VAL; ++v) {
            dp[k][v] = 0;
        }
    }

    for (int i = 1; i <= n; ++i) {
        int val = a[i];
        for (int k = 12; k >= 2; --k) {
            for (int v = 0; v < MAX_VAL; ++v) {
                if (dp[k-1][v ^ val] != 0) {
                    dp[k][v] = max(dp[k][v], dp[k-1][v ^ val]);
                }
            }
        }
        dp[1][val] = i;

        for (const auto& qry : queries[i]) {
            int l = get<0>(qry);
            int x = get<1>(qry);
            int id = get<2>(qry);

            int found_size = 0;
            for (int k = 1; k <= 12; ++k) {
                if (dp[k][x] >= l) {
                    found_size = k;
                    break;
                }
            }
            ans[id] = found_size;
        }
    }
    for (int i = 0; i < q; ++i) {
        cout << ans[i] << " ";
    }

    return 0;
}
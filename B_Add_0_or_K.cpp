#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n, k;
    cin >> n >> k;
    vector<long long> a(n);
    for (auto &i : a) {
      cin >> i;
    }

    for (int g = 2;; g++) {
      if (gcd(g, k) != 1)
        continue;
      for (auto &i : a) {
        while (i % g != 0)
          i += k;
      }
      for (auto i : a)
        cout << i << ' ';
      cout << '\n';
      break;
    }
  }
}
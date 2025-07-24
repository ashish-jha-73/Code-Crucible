#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> v(n + 1, -1);
    int cnt = 0;
    for (int i{1}; i<=n; ++i) {
        std::cin >> v[i];
        cnt += std::max(0, v[i-1] - v[i]);
    }

    std::cout << cnt;
}
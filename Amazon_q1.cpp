#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> v(n);
    int cnt = 1;
    int val = -1;
    for (int i{0}; i<n; i++) {
        std::cin >> v[i];
        if (i == 0) val = v[i];
        else cnt += (v[i] <= val);
    }

    std::cout << cnt << std::endl;
}
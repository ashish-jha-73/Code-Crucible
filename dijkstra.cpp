#include <bits/stdc++.h>
#include <debug_template>
using namespace std;

int main() {
    vector<vector<int>> v;
    for (int i{0}; i<10; i++) {
        vector<int> temp;
        for (int j{0}; j<10; j++) {
            temp.push_back(j);
        }
        v.push_back(temp);
    }

    debug(v);
}
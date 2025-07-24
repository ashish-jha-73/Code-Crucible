#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int max_conn;
vector<vector<pair<int, int>>> adj;
vector<vector<long long>> memo;

long long rec(int u, int parent, bool parent_edge_kept) {
    int state = parent_edge_kept ? 1 : 0;

    if (memo[u][state] != -1)
        return memo[u][state];

    long long base = 0;
    vector<long long> gains;

    for (auto &[v, w] : adj[u]) {
        if (v == parent) continue;

        long long drop = rec(v, u, false);
        long long keep = rec(v, u, true) + w;
        base += drop;
        gains.push_back(keep - drop);
    }

    sort(gains.rbegin(), gains.rend());

    int budget = max_conn - (parent_edge_kept ? 1 : 0);
    long long result = base;

    for (int i = 0; i < min((int)gains.size(), budget); ++i) {
        if (gains[i] > 0)
            result += gains[i];
        else
            break;
    }

    return memo[u][state] = result;
}

long long getMaxLoad(
    int max_connections,
    int service_nodes,
    vector<int>& service_from,
    vector<int>& service_to,
    vector<int>& service_weight
) {
    int N = service_nodes;
    max_conn = max_connections;
    adj.assign(N, {});
    memo.assign(N, vector<long long>(2, -1));

    for (int i = 0; i < service_from.size(); ++i) {
        int u = service_from[i];
        int v = service_to[i];
        int w = service_weight[i];
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    // Start from root = 0, no parent ⇒ parent_edge_kept = false
    return rec(0, -1, false);
}


int main() {
    // Example from prompt:
    int service_nodes = 5;
    vector<int> service_from = {0, 0, 2, 2};
    vector<int> service_to   = {1, 2, 3, 4};
    vector<int> service_weight = {10, 5, 30, 15};
    int max_connections = 2;

    long long result = getMaxLoad(max_connections,
                           service_nodes,
                           service_from,
                           service_to,
                           service_weight);

    cout << "Maximum retained load = " << result << '\n';
    // Expected output: 55
    return 0;
}

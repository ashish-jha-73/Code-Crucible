#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = LLONG_MAX;
struct State {
    ll cost, mini, maxi;
    int node;
    State(ll c, ll mi, ll ma, int v) : cost(c), mini(mi), maxi(ma), node(v) {}
    bool operator>(State const &o) const {
        return cost > o.cost;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        int N = 2*n + 2;
        vector<vector<pair<int,ll>>> graph(N);

        for (int i = 0; i < m; i++) {
            int u, v;
            ll w;
            cin >> u >> v >> w;
            // layer 1
            graph[u].push_back({v, w});
            graph[v].push_back({u, w});
            // layer 2
            graph[u+n].push_back({v+n, w});
            graph[v+n].push_back({u+n, w});
            // transitions to copy-layer
            if (u != 1) graph[u].push_back({u+n, -1});
            if (v != 1) graph[v].push_back({v+n, -1});
        }

        // Dijkstra on state space
        queue<State> q;
        set<ll> seen;
        auto encode = [&](int node, ll mi, ll ma) {
            size_t h1 = ((size_t)node << 32) ^ ((size_t)mi << 16) ^ (size_t)ma;
            return (ll)h1;
        };

        // start from node 1 in layer1, no edges yet
        q.emplace(0, INF, -INF, 1);
        ll answer = INF;

        while (!q.empty()) {
            auto s = q.front(); q.pop();
            int u = s.node;
            ll c = s.cost, mi = s.mini, ma = s.maxi;
            // encode state
            ll key = encode(u, mi, ma);
            if (seen.count(key)) continue;
            seen.insert(key);

            if (u == n || u == n + n) {
                answer = min(answer, c);
            }

            for (auto &pr : graph[u]) {
                int v = pr.first;
                ll w = pr.second;
                ll nmi = mi, nma = ma;
                ll nc = c;
                if (w >= 0) {
                    nmi = (mi==INF ? w : min(mi, w));
                    nma = (ma==-INF ? w : max(ma, w));
                    nc = nmi + nma;
                }
                ll nk = encode(v, nmi, nma);
                if (!seen.count(nk)) {
                    q.emplace(nc, nmi, nma, v);
                }
            }
        }

        cout << answer << '\n';
    }
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

inline double xlogx(double x) {
    if (x < 0.5) return 0.0;
    return x * log2(x);
}

struct TrieNode {
    map<int, int> children;
    map<int, int> next_token_counts;
    int total_count = 0;
};

vector<TrieNode> trie;

void trie_insert(const vector<int>& text, int pos, int next_token) {
    int curr = 0;
    for (int i = pos - 1; i >= 0; --i) {
        int token = text[i];
        if (trie[curr].children.find(token) == trie[curr].children.end()) {
            trie[curr].children[token] = trie.size();
            trie.push_back(TrieNode());
        }
        curr = trie[curr].children[token];
    }
    
    trie[curr].next_token_counts[next_token]++;
    trie[curr].total_count++;
}

void process_trie(int max_len, vector<double>& diff_arr) {
    for (const auto& node : trie) {
        if (node.total_count == 0) continue;

        double term1 = xlogx(node.total_count);
        double term2 = 0;
        for (auto const& [tok, cnt] : node.next_token_counts) {
            term2 += xlogx(cnt);
        }
        double loss = term1 - term2;
    }
}

void trie_dfs(int u, int depth, vector<double>& diff_arr, int max_m) {
    if (trie[u].total_count > 0) {
        double term1 = xlogx(trie[u].total_count);
        double term2 = 0;
        for (auto const& [tok, cnt] : trie[u].next_token_counts) {
            term2 += xlogx(cnt);
        }
        double loss = term1 - term2;
        
        if (depth + 1 < diff_arr.size()) {
            diff_arr[depth + 1] += loss;
        }
    }
    
    for (auto const& [tok, v] : trie[u].children) {
        trie_dfs(v, depth + 1, diff_arr, max_m);
    }
}

struct SuffixArray {
    vector<int> sa, lcp, rk;
    int n;

    SuffixArray(const vector<int>& s) {
        n = s.size();
        sa.resize(n);
        rk.resize(n);
        lcp.resize(n);
        vector<int> cnt(max((size_t)n, (size_t)300005), 0); 

        for (int i = 0; i < n; ++i) cnt[rk[i] = s[i]]++;
        for (int i = 1; i < cnt.size(); ++i) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; --i) sa[--cnt[s[i]]] = i;

        for (int k = 1; k < n; k <<= 1) {
            vector<int> p(n);
            int cur = 0;
            for (int i = n - k; i < n; ++i) p[cur++] = i;
            for (int i = 0; i < n; ++i) if (sa[i] >= k) p[cur++] = sa[i] - k;

            fill(cnt.begin(), cnt.end(), 0);
            for (int i = 0; i < n; ++i) cnt[rk[p[i]]]++;
            for (int i = 1; i < cnt.size(); ++i) cnt[i] += cnt[i - 1];
            for (int i = n - 1; i >= 0; --i) sa[--cnt[rk[p[i]]]] = p[i];

            vector<int> new_rk(n);
            new_rk[sa[0]] = 0;
            for (int i = 1; i < n; ++i) {
                pair<int, int> prev = {rk[sa[i - 1]], sa[i - 1] + k < n ? rk[sa[i - 1] + k] : -1};
                pair<int, int> now = {rk[sa[i]], sa[i] + k < n ? rk[sa[i] + k] : -1};
                new_rk[sa[i]] = new_rk[sa[i - 1]] + (prev != now);
            }
            rk = new_rk;
            if (rk[sa[n - 1]] == n - 1) break;
        }

        // Kasai's algorithm
        int k = 0;
        for (int i = 0; i < n; ++i) {
            if (rk[i] == n - 1) {
                k = 0;
                continue;
            }
            int j = sa[rk[i] + 1];
            while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
            lcp[rk[i]] = k;
            if (k > 0) k--;
        }
    }
};

struct DsuNode {
    map<int, int> counts; 
    int total_cnt = 0;
    double log_sum_parts = 0.0; 
    int parent = -1;
};

vector<DsuNode> dsu_nodes;
double current_global_sa_loss = 0;

int find_set(int v) {
    if (dsu_nodes[v].parent < 0) return v;
    return dsu_nodes[v].parent = find_set(dsu_nodes[v].parent);
}

double get_component_loss(int v) {
    if (dsu_nodes[v].total_cnt == 0) return 0.0;
    return xlogx(dsu_nodes[v].total_cnt) - dsu_nodes[v].log_sum_parts;
}

void merge_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (dsu_nodes[a].counts.size() < dsu_nodes[b].counts.size()) swap(a, b);
        
        current_global_sa_loss -= get_component_loss(a);
        current_global_sa_loss -= get_component_loss(b);

        dsu_nodes[a].total_cnt += dsu_nodes[b].total_cnt;
        for (auto const& [tok, cnt] : dsu_nodes[b].counts) {
            int old_cnt_a = dsu_nodes[a].counts[tok];
            dsu_nodes[a].log_sum_parts -= xlogx(old_cnt_a); 
            
            dsu_nodes[a].counts[tok] += cnt;
            dsu_nodes[a].log_sum_parts += xlogx(dsu_nodes[a].counts[tok]); 
        }
        
        current_global_sa_loss += get_component_loss(a);
        
        dsu_nodes[b].parent = a;
        dsu_nodes[b].counts.clear(); 
    }
}

void add_point(int u, int token) {
    u = find_set(u);
    current_global_sa_loss -= get_component_loss(u);
    
    int old_cnt = dsu_nodes[u].counts[token];
    dsu_nodes[u].log_sum_parts -= xlogx(old_cnt);
    
    dsu_nodes[u].counts[token]++;
    dsu_nodes[u].total_cnt++;
    dsu_nodes[u].log_sum_parts += xlogx(dsu_nodes[u].counts[token]);
    
    current_global_sa_loss += get_component_loss(u);
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    map<string, int> token_map;
    int token_counter = 0;
    auto get_token_id = [&](const string& s) {
        if (token_map.find(s) == token_map.end()) token_map[s] = ++token_counter;
        return token_map[s];
    };

    struct TextData {
        int m;
        vector<int> tokens;
        string mask;
    };
    vector<TextData> texts(n);
    int max_m = 0;
    
    for (int i = 0; i < n; ++i) {
        cin >> texts[i].m;
        max_m = max(max_m, texts[i].m);
        texts[i].tokens.resize(texts[i].m);
        for (int j = 0; j < texts[i].m; ++j) {
            string s; cin >> s;
            texts[i].tokens[j] = get_token_id(s);
        }
        cin >> texts[i].mask;
    }

    trie.push_back(TrieNode());
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < texts[i].m; ++j) {
            if (texts[i].mask[j] == 'L') {
                trie_insert(texts[i].tokens, j, texts[i].tokens[j]);
            }
        }
    }

    vector<double> trie_diff(max_m + 2, 0.0);
    trie_dfs(0, 0, trie_diff, max_m);

    for (int i = 1; i <= max_m; ++i) trie_diff[i] += trie_diff[i-1];
    vector<int> big_string;
    vector<pair<int, int>> map_pos; 
    
    int sep = token_counter + 1;
    for (int i = 0; i < n; ++i) {
        for (int j = texts[i].m - 1; j >= 0; --j) {
            big_string.push_back(texts[i].tokens[j]);
            if (j + 1 < texts[i].m && texts[i].mask[j+1] == 'L') {
                map_pos.push_back({texts[i].tokens[j+1], j + 1}); 
            } else {
                map_pos.push_back({-1, -1});
            }
        }
        big_string.push_back(sep++);
        map_pos.push_back({-1, -1});
    }
    vector<int> zero_len_tokens;
    for(int i=0; i<n; ++i) {
        if(texts[i].mask[0] == 'L') {
            zero_len_tokens.push_back(texts[i].tokens[0]);
        }
    }

    SuffixArray sa_algo(big_string);
    int N_SA = big_string.size();
    
    dsu_nodes.resize(N_SA);
    
    vector<vector<int>> merges(max_m + 1);
    for (int i = 0; i < N_SA - 1; ++i) {
        int len = sa_algo.lcp[i];
        if (len < max_m) {
            merges[len].push_back(i); 
        } else {
            merges[max_m].push_back(i); 
        }
    }
    vector<vector<pair<int,int>>> activations(max_m + 1);
    
    for (int i = 0; i < N_SA; ++i) {
        if (map_pos[i].first != -1) {
            int token = map_pos[i].first;
            int len = map_pos[i].second; 
            int sa_idx = sa_algo.rk[i];
            if (len < max_m)
                activations[len].push_back({sa_idx, token});
            else 
                activations[max_m].push_back({sa_idx, token});
        }
    }

    vector<double> results(max_m);
    
    for (int k = max_m - 1; k >= 1; --k) {
        if (k < activations.size()) {
            for (auto p : activations[k]) {
                add_point(p.first, p.second);
            }
        }
        if (k < merges.size()) {
            for (int idx : merges[k]) {
                merge_sets(idx, idx + 1);
            }
        }
        double total = current_global_sa_loss;
        if (k < trie_diff.size()) total += trie_diff[k];
        results[k] = total;
    }
    if (0 < activations.size()) {
        for (auto p : activations[0]) add_point(p.first, p.second);
    }
    for (int idx : merges[0]) merge_sets(idx, idx+1);

    int root = find_set(0); 
    for (int t : zero_len_tokens) {
        add_point(root, t);
    }
    
    double total_0 = current_global_sa_loss;
    if (0 < trie_diff.size()) total_0 += trie_diff[0];
    results[0] = total_0;

    cout << fixed << setprecision(12);
    for (int k = 0; k < max_m; ++k) {
        cout << results[k] << (k == max_m - 1 ? "" : "\n");
    }
    cout << endl;

    return 0;
}
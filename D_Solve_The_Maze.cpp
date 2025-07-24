#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;

/*
****************************************************************************************************************************************************************************************************************************************************************************
    Author :- Ikshvaku
    Yug :- Kaliyug (5126+ years elapsed)
    Manvantara :- 7th (Vaivasvata Manu)
    Mahayuga :- 28th of this Manvantara
    Kalpa :- Shveta-Varaha Kalpa
    Brahma Time :- 51st year, 1st day
****************************************************************************************************************************************************************************************************************************************************************************
*/

// Debugging Tools For CP
#ifndef ONLINE_JUDGE
#include <debug_template.hpp>
#else
#define debug(...)
#endif

typedef long double ld;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vector<ll>> vvl;
typedef vector<char> vc;
typedef pair<ll, ll> pll;
typedef pair<ll, char> plc;
#define fl(i, j) for(int i{0}; i<j; i++)
#define fb(i, j, k) for (int i{j}; i>=k; i--)
#define fn(i, j, k) for(int i{j}; i<k; i++)
#define no cout << "No\n"
#define yes cout << "Yes\n"
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define DEFINE_AND_READ(type, ...) type __VA_ARGS__; read(__VA_ARGS__)
#define d_n(...) DEFINE_AND_READ(ll, __VA_ARGS__)
#define d_s(...) DEFINE_AND_READ(string, __VA_ARGS__)
#define d_c(...) DEFINE_AND_READ(char, __VA_ARGS__)
#define d_d(...) DEFINE_AND_READ(ld, __VA_ARGS__)
#define d_v(v, n) vl v(n); fl(i, n) cin >> v[i]
#define en "\n"
#define F first
#define S second
#define PB push_back
#define PPB pop_back()
#define MP make_pair
#define B begin()
#define E end()

// Utility Function
template <class T> 
using ind_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>; 
template <typename T>
void pt(T &&t)  { cout << t << "\n"; }
template<typename T>
ll sv(vector<T>v){ll n=v.size();ll s=0;fl(i,n)s+=v[i];return s;}
template <typename T>
istream &operator>>(istream &istream, vector<T> &v)
{
    for (auto &it : v)
        cin >> it;
    return istream;
}
template <typename T>
ostream &operator<<(ostream &ostream, const vector<T> &c)
{
    for (auto &it : c)
        cout << it << " ";
    return ostream;
}
template<typename... T>
void read(T&... args) {
    (cin >> ... >> args);
}

// Number Theory
const ll MOD = 1e9+7, mod = MOD;
ll inv(ll i) {if (i == 1) return 1; return (mod - ((mod / i) * inv(mod % i)) % mod) % mod;}
ll mod_mul(ll a, ll b) {a = a % mod; b = b % mod; return (((a * b) % mod) + mod) % mod;}
ll mod_add(ll a, ll b) {a = a % mod; b = b % mod; return (((a + b) % mod) + mod) % mod;}
ll mod_sub(ll a, ll b) {a = a % mod; b = b % mod; return (((a - b + mod) % mod) + mod) % mod;}
ll ceil_div(ll a, ll b) {return a % b == 0 ? a / b : a / b + 1;}
ll pwr(ll a, ll b) {a %= mod; ll res = 1; while (b > 0) {if (b & 1) res = res * a % mod; a = a * a % mod; b >>= 1;} return res;}
vector<ll> sieve(int n) {int*arr = new int[n + 1](); vector<ll> vect; for (int i = 2; i <= n; i++)if (arr[i] == 0) {vect.push_back(i); for (int j = 2 * i; j <= n; j += i)arr[j] = 1;} return vect;}
ll modpow(ll x, ll n, int m = MOD){if (x == 0 && n == 0) return 0; ll res = 1; while (n > 0){ if (n % 2) res = (res * x) % m; x = (x * x) % m; n /= 2; } return res; }
int modinv(int x, int m = MOD) { return modpow(x, m - 2, m);}
ll binToDec(string s) { return bitset<64>(s).to_ullong(); }
string decToBin(ll a) { return bitset<64>(a).to_string(); }
ll factorial(ll n){if (n==0){ return 1;} ll ans=1;for (ll i=1;i<=n;i++) { ans=mod_mul(ans,i); } return ans; }
ll nCr(ll n, ll r) { if (n<r){ return 0;} ll ans=factorial(n); ans=mod_mul(ans,inv(factorial(r))); ans=mod_mul(ans,inv(factorial(n-r))); return ans; }
vector<pair<int, int>> d = {{0, -1}, {-1, 0}, {1, 0}, {0, 1}};

bool check(vector<vector<char>> &maze, int i, int j, vector<vector<bool>> &possible) {
    int n = maze.size(), m = maze[0].size();
    vector<vector<bool>> vis(n, vector<bool>(m, 0));
    queue<pair<int, int>> q;
    q.push({i, j});
    vis[i][j] = 1;
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        if (possible[x][y]) return true;
        if (x == n - 1 and y == m - 1) return true;
        possible[x][y] = 1;
        for (auto &[dx, dy]: d) {
            auto nx = x + dx, ny = y + dy;
            if (nx >= 0 and nx < n and ny >= 0 and ny < m and maze[nx][ny] != '#') {
                if (!vis[nx][ny] and (maze[nx][ny] == '.' or maze[nx][ny] == 'G')) {
                    vis[nx][ny] = 1;
                    q.push({nx, ny});
                }
            }
        }
    }
    return false;
}

void solve(){
    // code here
    d_n(n, m);
    vector<vector<char>> maze(n, vector<char>(m, '.'));
    bool flag = false, flag1 = false;
    vector<pair<int, int>> v;
    fl(i, n) {
        fl(j, m) {
            char ch;
            cin >> ch;
            flag |= (ch == 'G');
            maze[i][j] = ch;
        }
    }
    if (!flag) {
        yes;
        return;
    }

    fl(i, n) {
        fl(j, m) {
            if (maze[i][j] == 'G') v.push_back({i, j});
            if (maze[i][j] == 'B') {
                for (auto &[dx, dy]: d) {
                    auto nx = i + dx, ny = j + dy;
                    debug(nx, ny);
                    if (nx >= 0 and nx < n and ny >= 0 and ny < m) {
                        if (maze[nx][ny] == '.' or maze[nx][ny] == '#') {
                            maze[nx][ny] = '#';
                        } else if (maze[nx][ny] == 'G'){
                            no;
                            return;
                        }
                    }
                }
            }
        }
    }
    debug(maze);
    debug(v);
    vector<vector<bool>> reachable(n, vector<bool>(m, false));
    queue<pair<int, int>> q;

    if (maze[n - 1][m - 1] != '#') {
        q.push({n - 1, m - 1});
        reachable[n - 1][m - 1] = true;
    }

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        for (auto &[dx, dy] : d) {
            int nx = x + dx, ny = y + dy;
            if (nx >= 0 && nx < n && ny >= 0 && ny < m &&
                maze[nx][ny] != '#' && !reachable[nx][ny]) {
                reachable[nx][ny] = true;
                q.push({nx, ny});
            }
        }
    }

    for (auto &[i, j] : v) {
        if (!reachable[i][j]) {
            no;
            return;
        }
    }
    // yes;
    vector<vector<bool>> possible(n, vector<bool>(m, 0));
    if (!check(maze, v[0].first, v[0].second, possible)){
        no;
        return;
    }
    yes;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    d_n(t);
    while (t--){
        solve();
    }
    return 0;
}   
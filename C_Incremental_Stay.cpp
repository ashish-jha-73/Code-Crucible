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
#include <debugtemplate>
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
#define no cout << "NO\n"
#define yes cout << "YES\n"
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

void fill(vl &v, ll &b, int j) {
    for (int i{j}; i<v.size()-1; i+=2) {
        b += v[i + 1] - v[i];
    }
}

void pref(vl &a) {
    ll sum = 0;
    fl (i, a.size()) {
        a[i] = a[i] + sum;
        sum = a[i];
    }
}

void solve(){
    // code here
    d_n(n);
    d_v(v, 2 * n);
    vl a;
    a.push_back(0);
    for (int i{0}; i<n; i++) {
        a.push_back(v[2 * n - i - 1] - v[i]);
    }
    pref(a);
    debug(a);
    ll even = 0, odd = 0;
    fill(v, even, 0);
    fill(v, odd, 1);
    debug(even, odd);
    vl ans;
    int j = 2 * n - 1;
    for (int i{1}; i<=n; i++, j--) {
        ll val = a[i - 1];
        if (i & 1) {
            val += even;
            even -= (v[i] - v[i - 1]) + (v[j] - v[j - 1]);
        } else {
            val += odd;
            odd -= (v[i] - v[i - 1]) + (v[j] - v[j - 1]);
        }
        ans.push_back(val);
    }

    cout << ans << endl;

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
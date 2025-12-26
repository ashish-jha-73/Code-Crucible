#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

// Sieve to generate primes.
// For n=700 (or even 5000), k is roughly n/2.
// We need enough primes. 10,000 is plenty.
vector<ll> primes;
void sieve(int n) {
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int p = 2; p * p <= n; p++) {
        if (is_prime[p]) {
            for (int i = p * p; i <= n; i += p)
                is_prime[i] = false;
        }
    }
    for (int p = 2; p <= n; p++) {
        if (is_prime[p]) primes.push_back(p);
    }
}

void solve() {
    int n;
    cin >> n;

    if (n == 1) {
        cout << primes[0] << "\n";
        return;
    }

    // 1. Find minimal k such that capacity >= n - 1
    int k = 1;
    while (true) {
        int cap;
        if (k == 1) cap = 1;
        else if (k == 2) cap = 3;
        else if (k == 3) cap = 6;
        else cap = 2 * k + 1; // k self + k cycle + 1 jump
        
        if (cap >= n - 1) break;
        k++;
    }

    // 2. Construct the values x[0]...x[k-1]
    vector<ll> x(k);
    if (k == 1) {
        x[0] = primes[0];
    } else if (k == 2) {
        // Special linear chain for k=2 to ensure distinctness
        // x0 = p0*p1, x1 = p1*p2. GCD(x0,x1)=p1.
        x[0] = primes[0] * primes[1];
        x[1] = primes[1] * primes[2];
    } else {
        // Cyclic construction for k >= 3
        // x_i shares p_(i+1) with x_(i+1)
        for (int i = 0; i < k; ++i) {
            x[i] = primes[i] * primes[(i + 1) % k];
        }
    }

    // 3. Define the Skeleton Path (Indices to visit)
    vector<int> skeleton;
    if (k == 1) {
        // Just stay at 0
        for(int i=0; i<n; i++) skeleton.push_back(0);
    } 
    else if (k == 2) {
        // Simple path 0 -> 1
        skeleton.push_back(0);
        skeleton.push_back(1);
    } 
    else {
        // k >= 3
        // Check if we require the specific "Jump" edge (GCD=1) to fit n-1 edges.
        // This occurs if k >= 4 and we are at the absolute limit of capacity.
        // For k=3, cap is 6. 2k+1 calculation gives 7, but jump doesn't exist for k=3. 
        // Formula used in loop handles cap logic, but strictly the jump exists only for k>=4.
        bool need_jump = (k >= 4 && (n - 1) == (2 * k + 1));

        if (need_jump) {
            // Eulerian path covering cycle + chord (0-2)
            // 0 -> 1 -> 2 -> 3 ... -> k-1 -> 0 -> 2
            for (int i = 0; i < k; ++i) skeleton.push_back(i);
            skeleton.push_back(0);
            skeleton.push_back(2);
        } else {
            // Standard Cycle: 0 -> 1 -> ... -> k-1 -> 0 ...
            // Add enough nodes to cover the needs
            for (int i = 0; i < k; ++i) skeleton.push_back(i);
            skeleton.push_back(0);
            // Just in case n is small relative to capacity but wraps around
            for (int i = 1; i < k; ++i) skeleton.push_back(i); 
        }
    }

    // 4. Build Result
    vector<ll> res;
    vector<bool> used_self(k, false);

    // We iterate through skeleton. 
    // Logic: Output node. If self-loop not used, output again (implies self-loop edge).
    
    for (int node : skeleton) {
        if (res.size() == n) break;
        
        res.push_back(x[node]);
        
        if (res.size() == n) break;

        if (!used_self[node]) {
            res.push_back(x[node]);
            used_self[node] = true;
        }
    }

    // Output
    for (int i = 0; i < n; ++i) {
        cout << res[i] << (i == n - 1 ? "" : " ");
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    sieve(20000); 
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
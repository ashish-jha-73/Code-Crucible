#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void solve() {
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;

    long long fixed_val_sum = 0;
    long long fixed_pairs = 0;
    
    long long base_pairs_from_segs = 0;
    long long cap_plus = 0;
    long long cap_zero = 0;
    long long total_q = 0;

    for (int i = 0; i < n; ) {
        if (s[i] != '?') {
            if (s[i] == 'X') fixed_val_sum += 10;
            else if (s[i] == 'V') fixed_val_sum += 5;
            else fixed_val_sum += 1;

            if (s[i] == 'I' && i + 1 < n && s[i+1] != '?' && (s[i+1] == 'X' || s[i+1] == 'V')) {
                fixed_pairs++;
            }
            i++;
        } else {
            int j = i;
            while (j < n && s[j] == '?') {
                j++;
            }
            int len = j - i;
            total_q += len;

            bool left_is_I = (i > 0 && s[i-1] == 'I');
            bool right_is_XV = (j < n && (s[j] == 'X' || s[j] == 'V'));

            if (left_is_I && right_is_XV) {
                base_pairs_from_segs += 1;
                cap_plus += len / 2;
                if (len % 2 != 0) cap_zero += 1;
            } else if (left_is_I && !right_is_XV) { 
                base_pairs_from_segs += 1;
                cap_plus += (len - 1) / 2;
                if (len % 2 == 0) cap_zero += 1;
            } else if (!left_is_I && right_is_XV) { 
                base_pairs_from_segs += 0;
                cap_plus += (len + 1) / 2;
                if (len % 2 == 0) cap_zero += 1;
            } else { 
                base_pairs_from_segs += 0;
                cap_plus += len / 2;
                if (len % 2 != 0) cap_zero += 1;
            }

            i = j;
        }
    }

    for (int k = 0; k < q; ++k) {
        long long cx, cv, ci;
        cin >> cx >> cv >> ci;
        
        long long use_i = min(total_q, ci);
        long long rem = total_q - use_i;
        long long use_v = min(rem, cv);
        long long use_x = rem - use_v;

        long long current_val = fixed_val_sum;
        current_val += use_i * 1;
        current_val += use_v * 5;
        current_val += use_x * 10;
        
        long long pairs = fixed_pairs + base_pairs_from_segs;
        
        long long plus_gain = min(use_i, cap_plus);
        long long remaining_i = use_i - plus_gain;
        long long zero_gain = min(remaining_i, cap_zero);
        long long minus_gain = remaining_i - zero_gain;
        
        pairs += plus_gain;
        pairs -= minus_gain; 
        
        cout << current_val - 2 * pairs << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
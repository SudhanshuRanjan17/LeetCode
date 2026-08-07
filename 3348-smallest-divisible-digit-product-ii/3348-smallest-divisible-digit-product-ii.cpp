#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    string smallestNumber(string num, long long t) {
        long long temp = t;
        int p2 = 0, p3 = 0, p5 = 0, p7 = 0;
        
        while (temp % 2 == 0) { p2++; temp /= 2; }
        while (temp % 3 == 0) { p3++; temp /= 3; }
        while (temp % 5 == 0) { p5++; temp /= 5; }
        while (temp % 7 == 0) { p7++; temp /= 7; }
        
        // If t has prime factors other than 2, 3, 5, 7, it's impossible.
        if (temp > 1) return "-1";
        
        int n = num.length();
        
        // Precompute prime factors for digits 1 to 9
        vector<vector<int>> d_factors(10, vector<int>(4, 0));
        for (int d = 1; d <= 9; ++d) {
            int val = d;
            while (val % 2 == 0) { d_factors[d][0]++; val /= 2; }
            while (val % 3 == 0) { d_factors[d][1]++; val /= 3; }
            while (val % 5 == 0) { d_factors[d][2]++; val /= 5; }
            while (val % 7 == 0) { d_factors[d][3]++; val /= 7; }
        }

        // Returns minimum length of non-zero digits needed to cover remaining factors
        auto min_digits_needed = [&](int c2, int c3, int c5, int c7) {
            c2 = max(0, c2);
            c3 = max(0, c3);
            c5 = max(0, c5);
            c7 = max(0, c7);
            
            int d9 = c3 / 2; c3 %= 2;
            int d8 = c2 / 3; c2 %= 3;
            int d7 = c7;
            int d5 = c5;
            int d6 = 0;
            if (c3 == 1 && c2 == 1) { d6 = 1; c3 = 0; c2 = 0; }
            int d4 = c2 / 2; c2 %= 2;
            int d3 = c3;
            int d2 = c2;
            
            return d2 + d3 + d4 + d5 + d6 + d7 + d8 + d9;
        };

        // Construct the lexicographically smallest suffix of length `len` covering requirements
        auto build_suffix = [&](int len, int c2, int c3, int c5, int c7) {
            string suffix = "";
            for (int pos = 0; pos < len; ++pos) {
                int slots_left = len - 1 - pos;
                for (int d = 1; d <= 9; ++d) {
                    int nc2 = c2 - d_factors[d][0];
                    int nc3 = c3 - d_factors[d][1];
                    int nc5 = c5 - d_factors[d][2];
                    int nc7 = c7 - d_factors[d][3];
                    
                    if (min_digits_needed(nc2, nc3, nc5, nc7) <= slots_left) {
                        suffix += to_string(d);
                        c2 = nc2; c3 = nc3; c5 = nc5; c7 = nc7;
                        break;
                    }
                }
            }
            return suffix;
        };

        // Find the prefix length before encountering any '0'
        int zero_pos = n;
        for (int i = 0; i < n; ++i) {
            if (num[i] == '0') {
                zero_pos = i;
                break;
            }
        }

        // Prefix factor prefix sums
        vector<int> pref_2(n + 1, 0), pref_3(n + 1, 0), pref_5(n + 1, 0), pref_7(n + 1, 0);
        for (int i = 0; i < zero_pos; ++i) {
            int d = num[i] - '0';
            pref_2[i + 1] = pref_2[i] + d_factors[d][0];
            pref_3[i + 1] = pref_3[i] + d_factors[d][1];
            pref_5[i + 1] = pref_5[i] + d_factors[d][2];
            pref_7[i + 1] = pref_7[i] + d_factors[d][3];
        }

        // Check if original num (if zero-free) already satisfies the condition
        if (zero_pos == n && min_digits_needed(p2 - pref_2[n], p3 - pref_3[n], p5 - pref_5[n], p7 - pref_7[n]) <= 0) {
            return num;
        }

        // Try matching a prefix of length i, then incrementing the digit at position i
        for (int i = min(n - 1, zero_pos); i >= 0; --i) {
            int cur_d = num[i] - '0';
            for (int d = cur_d + 1; d <= 9; ++d) {
                int req2 = p2 - pref_2[i] - d_factors[d][0];
                int req3 = p3 - pref_3[i] - d_factors[d][1];
                int req5 = p5 - pref_5[i] - d_factors[d][2];
                int req7 = p7 - pref_7[i] - d_factors[d][3];
                
                int rem_len = n - 1 - i;
                if (min_digits_needed(req2, req3, req5, req7) <= rem_len) {
                    string ans = num.substr(0, i) + to_string(d);
                    ans += build_suffix(rem_len, req2, req3, req5, req7);
                    return ans;
                }
            }
        }

        // If length needs to be extended
        int req_len = max(n + 1, min_digits_needed(p2, p3, p5, p7));
        return build_suffix(req_len, p2, p3, p5, p7);
    }
};
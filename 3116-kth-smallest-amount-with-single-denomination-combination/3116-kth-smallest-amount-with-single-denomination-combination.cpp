class Solution {
public:
    using ll = long long;

    ll gcdll(ll a, ll b) {
        while (b) {
            ll t = a % b;
            a = b;
            b = t;
        }
        return a;
    }

    ll lcm(ll a, ll b, ll limit) {
        ll g = gcdll(a, b);

        // Prevent overflow and ignore LCM > limit
        if (a / g > limit / b)
            return limit + 1;

        return (a / g) * b;
    }

    long long countMultiples(long long x, vector<int>& coins) {
        int n = coins.size();
        long long ans = 0;

        // Inclusion-exclusion over all subsets
        for (int mask = 1; mask < (1 << n); mask++) {
            ll currentLCM = 1;
            int bits = 0;
            bool valid = true;

            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) {
                    bits++;

                    currentLCM = lcm(currentLCM, coins[i], x);

                    if (currentLCM > x) {
                        valid = false;
                        break;
                    }
                }
            }

            if (!valid)
                continue;

            ll ways = x / currentLCM;

            if (bits % 2 == 1)
                ans += ways;
            else
                ans -= ways;
        }

        return ans;
    }

    long long findKthSmallest(vector<int>& coins, long long k) {

        // Remove redundant coins.
        // If coins[i] is divisible by coins[j],
        // then every multiple of coins[i] is already counted by coins[j].
        sort(coins.begin(), coins.end());

        vector<int> useful;

        for (int coin : coins) {
            bool redundant = false;

            for (int x : useful) {
                if (coin % x == 0) {
                    redundant = true;
                    break;
                }
            }

            if (!redundant)
                useful.push_back(coin);
        }

        coins = useful;

        // Binary search range
        //
        // The kth answer can never exceed minCoin * k.
        ll low = 1;
        ll high = 1LL * coins[0] * k;

        while (low < high) {
            ll mid = low + (high - low) / 2;

            if (countMultiples(mid, coins) >= k)
                high = mid;
            else
                low = mid + 1;
        }

        return low;
    }
};
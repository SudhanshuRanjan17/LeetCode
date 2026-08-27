class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.size();

        // cnt[i][c] = number of character c remaining
        // after using target[0 ... i-1]
        vector<array<int, 26>> cnt(n + 1);

        for (int c = 0; c < 26; c++)
            cnt[0][c] = 0;

        for (char ch : s)
            cnt[0][ch - 'a']++;

        // Build remaining frequencies for every prefix
        vector<bool> possible(n + 1, false);
        possible[0] = true;

        for (int i = 0; i < n; i++) {
            cnt[i + 1] = cnt[i];

            int c = target[i] - 'a';

            if (possible[i] && cnt[i][c] > 0) {
                cnt[i + 1][c]--;
                possible[i + 1] = true;
            } else {
                possible[i + 1] = false;
            }
        }

        // Try changing the rightmost possible position first
        for (int i = n - 1; i >= 0; i--) {

            // target[0 ... i-1] must be constructible
            if (!possible[i])
                continue;

            int cur = target[i] - 'a';

            // Find the smallest character greater than target[i]
            for (int c = cur + 1; c < 26; c++) {

                if (cnt[i][c] == 0)
                    continue;

                string ans = target.substr(0, i);

                // Put the larger character here
                ans += char('a' + c);

                // Use it
                auto remaining = cnt[i];
                remaining[c]--;

                // Fill the suffix with smallest possible characters
                for (int x = 0; x < 26; x++) {
                    while (remaining[x] > 0) {
                        ans += char('a' + x);
                        remaining[x]--;
                    }
                }

                return ans;
            }
        }

        return "";
    }
};
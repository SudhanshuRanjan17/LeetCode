class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        int n = s.size();

        // Required variable
        string calendrix = s;

        // Count characters
        vector<int> cnt(26, 0);
        for (char c : s) {
            cnt[c - 'a']++;
        }

        // A palindrome can have at most one odd frequency
        int odd = 0;
        char mid = 0;

        for (int i = 0; i < 26; i++) {
            if (cnt[i] % 2) {
                odd++;
                mid = char('a' + i);
            }
        }

        if (odd > 1)
            return "";

        // Characters available for the left half
        vector<int> halfCnt(26);
        for (int i = 0; i < 26; i++) {
            halfCnt[i] = cnt[i] / 2;
        }

        int half = n / 2;

        /*
            ---------------------------------------------------
            STEP 1:
            Try to make the left half exactly equal to
            target[0 ... half-1].
            ---------------------------------------------------
        */

        vector<int> rem = halfCnt;
        string left;

        bool possible = true;

        for (int i = 0; i < half; i++) {
            int c = target[i] - 'a';

            if (rem[c] == 0) {
                possible = false;
                break;
            }

            left.push_back(target[i]);
            rem[c]--;
        }

        /*
            If we can exactly match target's left half,
            construct the palindrome.

            This case is extremely important.

            Example:
                s = "aabb"
                target = "abaa"

                left = "ab"
                palindrome = "abba"

                "abba" > "abaa"

            Therefore "abba" is the answer.
        */

        if (possible) {
            string candidate = left;

            if (n % 2)
                candidate.push_back(mid);

            string right = left;
            reverse(right.begin(), right.end());

            candidate += right;

            if (candidate > target)
                return candidate;
        }

        /*
            ---------------------------------------------------
            STEP 2:
            We couldn't use the exact target prefix to obtain
            a valid answer.

            Now find the RIGHTMOST position where we can put
            a character greater than target[i].

            Why rightmost?

            Because changing a later position gives the
            lexicographically smallest possible answer.
            ---------------------------------------------------
        */

        int bestPos = -1;
        int bestChar = -1;

        rem = halfCnt;

        for (int i = 0; i < half; i++) {

            int t = target[i] - 'a';

            /*
                Try every character greater than target[i].
                The smallest such character is sufficient.
            */
            for (int c = t + 1; c < 26; c++) {
                if (rem[c] > 0) {
                    bestPos = i;
                    bestChar = c;
                    break;
                }
            }

            /*
                To continue matching target, target[i] itself
                must be available.
            */
            if (rem[t] == 0)
                break;

            rem[t]--;
        }

        if (bestPos == -1)
            return "";

        /*
            ---------------------------------------------------
            STEP 3:
            Construct the smallest left half.

            Prefix = same as target
            At bestPos = smallest possible larger character
            Suffix = all remaining characters sorted
            ---------------------------------------------------
        */

        rem = halfCnt;
        left.clear();

        // Match target prefix
        for (int i = 0; i < bestPos; i++) {
            int c = target[i] - 'a';

            left.push_back(target[i]);
            rem[c]--;
        }

        // Increase at bestPos
        left.push_back(char('a' + bestChar));
        rem[bestChar]--;

        // Fill remaining characters in ascending order
        for (int c = 0; c < 26; c++) {
            while (rem[c] > 0) {
                left.push_back(char('a' + c));
                rem[c]--;
            }
        }

        /*
            Build complete palindrome.
        */
        string ans = left;

        if (n % 2)
            ans.push_back(mid);

        string right = left;
        reverse(right.begin(), right.end());

        ans += right;

        return ans;
    }
};
class Solution:
    def distinctSubseqII(self, s: str) -> int:
        MOD = 10**9 + 7

        # dp[i] = number of distinct subsequences including empty
        # after processing characters so far
        total = 1

        # last[c] = number of subsequences that were created
        # the previous time character c appeared
        last = [0] * 26

        for ch in s:
            idx = ord(ch) - ord('a')

            new_total = (2 * total - last[idx]) % MOD

            # All subsequences formed by appending this character
            # are exactly 'total' before the update
            last[idx] = total

            total = new_total

        # Remove the empty subsequence
        return (total - 1) % MOD
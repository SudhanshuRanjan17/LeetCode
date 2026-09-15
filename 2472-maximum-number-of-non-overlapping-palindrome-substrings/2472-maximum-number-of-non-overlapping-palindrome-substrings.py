class Solution:
    def maxPalindromes(self, s: str, k: int) -> int:
        n = len(s)

        # dp[i] = maximum number of valid non-overlapping
        # palindromic substrings using s[0:i]
        dp = [0] * (n + 1)

        # pal[l] represents whether s[l:r+1] is a palindrome
        # for the previous value of r.
        pal = [False] * n

        for r in range(n):
            # Option 1: don't use a palindrome ending at r
            dp[r + 1] = dp[r]

            # IMPORTANT:
            # Iterate l from LEFT to RIGHT.
            # This keeps pal[l + 1] from the previous r,
            # which is exactly what we need for:
            # s[l+1:r]
            for l in range(r + 1):
                if s[l] == s[r] and (r - l <= 1 or pal[l + 1]):
                    pal[l] = True

                    length = r - l + 1

                    if length >= k:
                        dp[r + 1] = max(dp[r + 1], dp[l] + 1)
                else:
                    pal[l] = False

        return dp[n]
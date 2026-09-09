class Solution:
    def countCommas(self, n: int) -> int:
        ans = 0

        # Numbers with 1, 2, 3 digits have 0 commas.
        start = 1000

        # Numbers with at least 4 digits can contain commas.
        while start <= n:
            end = min(n, start * 1000 - 1)

            # All numbers in [start, end] have the same
            # number of commas.
            commas = len(str(start)) // 3

            ans += (end - start + 1) * commas

            start *= 1000

        return ans
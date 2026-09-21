class Solution:
    def resultArray(self, nums, k):
        ans = [0] * k
        dp = [0] * k

        for num in nums:
            new_dp = [0] * k
            mod = num % k

            # Start a new subarray
            new_dp[mod] = 1

            # Extend previous subarrays
            for r in range(k):
                new_dp[(r * mod) % k] += dp[r]

            # Add counts
            for r in range(k):
                ans[r] += new_dp[r]

            dp = new_dp

        return ans
from typing import List

class Solution:
    def predictTheWinner(self, nums: List[int]) -> bool:
        n = len(nums)
        dp = nums[:]
        
        for j in range(1, n):
            for i in range(j - 1, -1, -1):
                dp[i] = max(
                    nums[i] - dp[i + 1],
                    nums[j] - dp[i]
                )
        
        return dp[0] >= 0
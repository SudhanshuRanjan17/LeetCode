
from typing import List

class Solution:
    def minOperations(self, nums: List[int]) -> int:
        n = len(nums)
        k = nums[0]

        increasing = True
        decreasing = True

        for i in range(n):
            if nums[i] != (k + i) % n:
                increasing = False
            if nums[i] != (k - i) % n:
                decreasing = False

        if increasing:
            return min((n - k) % n, k + 2)

        if decreasing:
            return 1 + min((k + 1) % n, (n - k - 1) % n)

        return -1

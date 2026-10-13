from typing import List

class Solution:
    def maxAlternatingSum(self, nums: List[int]) -> int:
        squares = sorted((x * x for x in nums), reverse=True)
        n = len(nums)
        k = (n + 1) // 2

        return sum(squares[:k]) - sum(squares[k:])
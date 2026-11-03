
class Solution:
    def minMoves(self, nums: List[int]) -> int:
        n = len(nums)
        maxVal = 0
        totalSum = 0

        for i in range(n):
            totalSum += nums[i]

            if nums[i] > maxVal:
                maxVal = nums[i]

        return maxVal * n - totalSum
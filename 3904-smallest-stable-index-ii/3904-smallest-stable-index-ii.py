class Solution:
    def firstStableIndex(self, nums, k):
        n = len(nums)

        # suffix_min[i] = minimum value from nums[i] to nums[n-1]
        suffix_min = [0] * n
        suffix_min[n - 1] = nums[n - 1]

        for i in range(n - 2, -1, -1):
            suffix_min[i] = min(nums[i], suffix_min[i + 1])

        # Maximum value from nums[0] to nums[i]
        max_prefix = nums[0]

        # Find the first (smallest) stable index
        for i in range(n):
            max_prefix = max(max_prefix, nums[i])

            if max_prefix - suffix_min[i] <= k:
                return i

        return -1
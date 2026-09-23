class Solution:
    def minOperations(self, nums: list[int], x: int) -> int:
        total = sum(nums)
        target = total - x
        n = len(nums)

        # If we need to keep nothing
        if target == 0:
            return n

        # If target is impossible
        if target < 0:
            return -1

        left = 0
        current_sum = 0
        max_len = -1

        for right in range(n):
            current_sum += nums[right]

            # Shrink window if sum becomes too large
            while current_sum > target and left <= right:
                current_sum -= nums[left]
                left += 1

            # Found a valid subarray
            if current_sum == target:
                max_len = max(max_len, right - left + 1)

        return -1 if max_len == -1 else n - max_len

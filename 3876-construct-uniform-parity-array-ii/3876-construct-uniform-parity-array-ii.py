class Solution:
    def uniformArray(self, nums1: list[int]) -> bool:
        mn = min(nums1)

        # If the minimum is odd, it can convert every larger even
        # number into odd: even - odd = odd.
        if mn % 2 == 1:
            return True

        # If the minimum is even, every element must already be even.
        return all(x % 2 == 0 for x in nums1)
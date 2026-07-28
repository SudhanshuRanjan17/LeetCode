from collections import Counter
from string import ascii_lowercase

class Solution:
    def smallestPalindrome(self, s: str) -> str:
        cnt = Counter(s)
        left = []
        mid = ""
        for c in ascii_lowercase:
            pairs = cnt[c] // 2
            left.append(c * pairs)
            if cnt[c] % 2:
                mid = c
        left = "".join(left)
        return left + mid + left[::-1]
class Solution:
    def minimumPushes(self, word: str) -> int:
        n = len(word)
        k = n // 8      # number of complete groups of 8
        r = n % 8       # leftover letters
        
        # 8 * (1 + 2 + ... + k) + r * (k + 1)
        return 4 * k * (k + 1) + r * (k + 1)
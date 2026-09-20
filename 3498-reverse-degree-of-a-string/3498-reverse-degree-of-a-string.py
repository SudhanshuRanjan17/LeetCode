class Solution:
    def reverseDegree(self, s: str) -> int:
        total = 0

        for i, ch in enumerate(s):
            reverse_position = 26 - (ord(ch) - ord('a'))
            position = i + 1

            total += reverse_position * position

        return total
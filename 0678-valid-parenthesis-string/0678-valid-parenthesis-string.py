class Solution:
    def checkValidString(self, s: str) -> bool:
        low = 0
        high = 0

        for ch in s:
            if ch == '(':
                low += 1
                high += 1

            elif ch == ')':
                low = max(0, low - 1)
                high -= 1

            else:  # '*'
                low = max(0, low - 1)  # '*' acts as ')'
                high += 1              # '*' acts as '('

            # Even the most optimistic case cannot be valid
            if high < 0:
                return False

        # A valid string must be able to have zero unmatched '('
        return low == 0
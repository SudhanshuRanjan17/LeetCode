class Solution:
    def longestValidParentheses(self, s: str) -> int:
        stack = [-1]
        max_length = 0

        for i, ch in enumerate(s):
            if ch == '(':
                stack.append(i)
            else:
                stack.pop()

                if not stack:
                    # This ')' cannot be matched.
                    # It becomes the new starting boundary.
                    stack.append(i)
                else:
                    # Current valid substring starts after stack[-1]
                    max_length = max(max_length, i - stack[-1])

        return max_length
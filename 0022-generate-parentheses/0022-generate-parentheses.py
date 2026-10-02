class Solution:
    def generateParenthesis(self, n: int) -> list[str]:
        result = []

        def backtrack(current, open_count, close_count):
            # A valid combination is complete
            if len(current) == 2 * n:
                result.append(current)
                return

            # We can add '(' if we still have some left
            if open_count < n:
                backtrack(current + "(", open_count + 1, close_count)

            # We can add ')' only when it won't make the sequence invalid
            if close_count < open_count:
                backtrack(current + ")", open_count, close_count + 1)

        backtrack("", 0, 0)
        return result
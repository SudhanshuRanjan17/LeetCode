class Solution:
    def braceExpansionII(self, expression: str):
        n = len(expression)
        i = 0

        def multiply(A, B):
            result = set()

            for a in A:
                for b in B:
                    result.add(a + b)

            return result

        def parse():
            nonlocal i

            # Result of union at this level
            result = set()

            # Result of concatenation
            current = {""}

            while i < n and expression[i] != '}':
                ch = expression[i]

                if ch == ',':
                    # Finish current concatenation and add to union
                    result.update(current)
                    current = {""}
                    i += 1

                elif ch == '{':
                    i += 1
                    part = parse()
                    i += 1  # skip '}'

                    current = multiply(current, part)

                else:
                    # Lowercase letter
                    current = multiply(current, {ch})
                    i += 1

            # Add the final concatenation
            result.update(current)

            return result

        return sorted(parse())
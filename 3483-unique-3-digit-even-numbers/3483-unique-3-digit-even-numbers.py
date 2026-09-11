class Solution:
    def totalNumbers(self, digits: list[int]) -> int:
        # Count how many times each digit appears
        freq = [0] * 10

        for d in digits:
            freq[d] += 1

        ans = 0

        # Check every 3-digit even number
        for num in range(100, 1000, 2):
            # Extract its three digits
            a = num // 100
            b = (num // 10) % 10
            c = num % 10

            # Required digit frequencies for this number
            need = [0] * 10
            need[a] += 1
            need[b] += 1
            need[c] += 1

            # Check whether we have enough copies
            possible = True

            for d in range(10):
                if need[d] > freq[d]:
                    possible = False
                    break

            if possible:
                ans += 1

        return ans
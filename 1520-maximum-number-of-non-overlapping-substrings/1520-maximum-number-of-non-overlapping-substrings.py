class Solution:
    def maxNumOfSubstrings(self, s: str):
        n = len(s)

        first = [n] * 26
        last = [-1] * 26

        # Step 1: Find first and last occurrence
        for i, ch in enumerate(s):
            idx = ord(ch) - ord('a')
            first[idx] = min(first[idx], i)
            last[idx] = i

        intervals = []

        # Step 2: Build valid intervals
        for c in range(26):
            if first[c] == n:
                continue

            l = first[c]
            r = last[c]
            i = l
            valid = True

            while i <= r:
                idx = ord(s[i]) - ord('a')

                if first[idx] < l:
                    valid = False
                    break

                r = max(r, last[idx])
                i += 1

            if valid:
                intervals.append((l, r))

        # Step 3: Sort by ending index
        intervals.sort(key=lambda x: x[1])

        # Step 4: Greedily select non-overlapping intervals
        result = []
        prev_end = -1

        for l, r in intervals:
            if l > prev_end:
                result.append(s[l:r + 1])
                prev_end = r

        return result
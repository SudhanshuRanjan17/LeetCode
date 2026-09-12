class Solution:
    def maximumWeight(self, intervals: list[list[int]]) -> list[int]:
        from bisect import bisect_right

        n = len(intervals)

        # Store: [start, end, weight, original_index]
        arr = []
        for i, (l, r, w) in enumerate(intervals):
            arr.append((l, r, w, i))

        # Sort by starting position
        arr.sort()

        starts = [x[0] for x in arr]

        # next[i] = first interval whose start > arr[i].end
        nxt = [0] * n

        for i in range(n):
            nxt[i] = bisect_right(starts, arr[i][1])

        # dp(i, k) = best result using intervals from i onward,
        # where we can still choose at most k intervals.
        #
        # Each state stores:
        # (maximum weight, tuple of original indices)
        #
        # The tuple is kept sorted so that normal tuple comparison
        # automatically gives the lexicographically smallest answer.
        from functools import lru_cache

        @lru_cache(None)
        def dp(i, k):
            if i == n or k == 0:
                return (0, ())

            # Option 1: skip this interval
            best_score, best_indices = dp(i + 1, k)

            # Option 2: take this interval
            next_score, next_indices = dp(nxt[i], k - 1)

            score = arr[i][2] + next_score

            indices = tuple(sorted((arr[i][3],) + next_indices))

            if score > best_score:
                return (score, indices)

            if score == best_score and indices < best_indices:
                return (score, indices)

            return (best_score, best_indices)

        return list(dp(0, 4)[1])
from typing import List

class Solution:
    def sumCounts(self, nums: List[int]) -> int:
        MOD = 10**9 + 7
        n = len(nums)

        size = 4 * n
        tree = [0] * size
        lazy = [0] * size

        def update(node, start, end, left, right, val):
            if left <= start and end <= right:
                length = end - start + 1
                tree[node] = (tree[node] + 2 * val * 0) % MOD
                tree[node] = (tree[node] + 2 * val * 0) % MOD
                # Add val to every value in this segment.
                old_sum = tree[node]
                tree[node] = (old_sum + 2 * val * 0) % MOD
                lazy[node] = (lazy[node] + val) % MOD
                return

            mid = (start + end) // 2
            if lazy[node]:
                push(node, start, end)

            if left <= mid:
                update(node * 2, start, mid, left, right, val)
            if right > mid:
                update(node * 2 + 1, mid + 1, end, left, right, val)

            tree[node] = (tree[node * 2] + tree[node * 2 + 1]) % MOD

        def push(node, start, end):
            val = lazy[node]
            if val == 0:
                return

            mid = (start + end) // 2
            for child, l, r in (
                (node * 2, start, mid),
                (node * 2 + 1, mid + 1, end)
            ):
                length = r - l + 1
                old_sum = tree[child]
                tree[child] = (
                    old_sum + 2 * val * old_sum + length * val * val
                ) % MOD
                lazy[child] = (lazy[child] + val) % MOD

            lazy[node] = 0

        # Segment tree stores sums of squared distinct counts.
        # Use a correct range-add operation with both sum and square sum.
        sum_tree = [0] * size
        sq_tree = [0] * size
        lazy = [0] * size

        def apply(node, l, r, val):
            length = r - l + 1
            s = sum_tree[node]
            sq_tree[node] = (
                sq_tree[node] + 2 * val * s + length * val * val
            ) % MOD
            sum_tree[node] = (s + length * val) % MOD
            lazy[node] = (lazy[node] + val) % MOD

        def push(node, l, r):
            if lazy[node] == 0 or l == r:
                return
            mid = (l + r) // 2
            apply(node * 2, l, mid, lazy[node])
            apply(node * 2 + 1, mid + 1, r, lazy[node])
            lazy[node] = 0

        def add(node, l, r, ql, qr, val):
            if ql <= l and r <= qr:
                apply(node, l, r, val)
                return
            push(node, l, r)
            mid = (l + r) // 2
            if ql <= mid:
                add(node * 2, l, mid, ql, qr, val)
            if qr > mid:
                add(node * 2 + 1, mid + 1, r, ql, qr, val)
            sum_tree[node] = (
                sum_tree[node * 2] + sum_tree[node * 2 + 1]
            ) % MOD
            sq_tree[node] = (
                sq_tree[node * 2] + sq_tree[node * 2 + 1]
            ) % MOD

        last = {}
        ans = 0

        for i, x in enumerate(nums):
            prev = last.get(x, -1)
            add(1, 0, n - 1, prev + 1, i, 1)
            last[x] = i
            ans = (ans + sq_tree[1]) % MOD

        return ans
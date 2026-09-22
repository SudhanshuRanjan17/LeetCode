class Solution:
    def resultArray(self, nums, k, queries):
        n = len(nums)

        # Each node:
        # [product_mod_k, count_of_prefixes_for_each_remainder]
        size = 1
        while size < n:
            size <<= 1

        prod = [1] * (2 * size)
        cnt = [[0] * k for _ in range(2 * size)]

        # Build leaves
        for i in range(n):
            p = nums[i] % k
            pos = size + i

            prod[pos] = p
            cnt[pos][p] = 1

        # Merge two nodes
        def merge(left, right):
            lp = prod[left]
            rp = prod[right]

            new_prod = (lp * rp) % k
            new_cnt = [0] * k

            # Prefixes completely inside left
            lc = cnt[left]
            for r in range(k):
                new_cnt[r] += lc[r]

            # Prefixes that use all of left + a prefix of right
            rc = cnt[right]
            for r in range(k):
                c = rc[r]
                if c:
                    new_cnt[(lp * r) % k] += c

            return new_prod, new_cnt

        # Build tree
        for node in range(size - 1, 0, -1):
            p, c = merge(node * 2, node * 2 + 1)
            prod[node] = p
            cnt[node] = c

        # Point update
        def update(index, value):
            pos = size + index
            p = value % k

            prod[pos] = p
            cnt[pos] = [0] * k
            cnt[pos][p] = 1

            pos >>= 1

            while pos:
                p, c = merge(pos * 2, pos * 2 + 1)
                prod[pos] = p
                cnt[pos] = c
                pos >>= 1

        # Query a range [l, n-1]
        #
        # We need the number of prefixes of this range
        # whose product has remainder x.
        def query(l):
            left_nodes = []
            right_nodes = []

            l += size
            r = size + n

            while l < r:
                if l & 1:
                    left_nodes.append(l)
                    l += 1

                if r & 1:
                    r -= 1
                    right_nodes.append(r)

                l >>= 1
                r >>= 1

            # Process nodes from left to right.
            nodes = left_nodes + right_nodes[::-1]

            if not nodes:
                return [0] * k

            # Start with first segment.
            current_prod = prod[nodes[0]]
            current_cnt = cnt[nodes[0]][:]

            # Merge remaining segments
            for node in nodes[1:]:
                right_prod = prod[node]
                right_cnt = cnt[node]

                new_cnt = current_cnt[:]

                for r in range(k):
                    c = right_cnt[r]
                    if c:
                        new_cnt[(current_prod * r) % k] += c

                current_prod = (current_prod * right_prod) % k
                current_cnt = new_cnt

            return current_cnt

        answer = []

        for index, value, start, x in queries:
            update(index, value)

            counts = query(start)

            answer.append(counts[x])

        return answer
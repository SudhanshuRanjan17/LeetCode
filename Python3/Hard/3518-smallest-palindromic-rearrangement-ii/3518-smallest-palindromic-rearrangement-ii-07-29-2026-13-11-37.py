from collections import Counter

class Solution:
    def smallestPalindrome(self, s: str, k: int) -> str:
        CAP = k  # we only care whether the count reaches k

        freq = Counter(s)

        half = [0] * 26
        mid = ""
        total = 0

        for ch, cnt in freq.items():
            if cnt % 2:
                mid = ch
            half[ord(ch) - 97] = cnt // 2
            total += cnt // 2

        def capped_binom(n, r, cap):
            if r < 0 or r > n:
                return 0
            r = min(r, n - r)
            res = 1
            for i in range(1, r + 1):
                res = (res * (n - r + i)) // i
                if res >= cap:
                    return cap
            return res

        def count_perm(cnt):
            rem = sum(cnt)
            ways = 1
            for c in cnt:
                if c:
                    comb = capped_binom(rem, c, CAP)
                    ways *= comb
                    if ways >= CAP:
                        return CAP
                    rem -= c
            return ways

        if count_perm(half) < k:
            return ""

        first = []

        for _ in range(total):
            for i in range(26):
                if half[i] == 0:
                    continue

                half[i] -= 1
                ways = count_perm(half)

                if ways >= k:
                    first.append(chr(i + 97))
                    break
                else:
                    k -= ways
                    half[i] += 1

        left = "".join(first)
        return left + mid + left[::-1]
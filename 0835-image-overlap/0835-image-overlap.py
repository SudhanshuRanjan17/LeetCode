class Solution:
    def largestOverlap(self, img1: list[list[int]], img2: list[list[int]]) -> int:
        n = len(img1)

        # Store coordinates of all 1s
        ones1 = []
        ones2 = []

        for r in range(n):
            for c in range(n):
                if img1[r][c] == 1:
                    ones1.append((r, c))
                if img2[r][c] == 1:
                    ones2.append((r, c))

        # shift[(dr, dc)] = number of overlapping 1s
        shift = {}

        for r1, c1 in ones1:
            for r2, c2 in ones2:
                dr = r2 - r1
                dc = c2 - c1

                shift[(dr, dc)] = shift.get((dr, dc), 0) + 1

        return max(shift.values(), default=0)
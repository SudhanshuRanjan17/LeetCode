class Solution:
    def isRectangleOverlap(self, rec1: list[int], rec2: list[int]) -> bool:
        # Find the intersection boundaries
        left = max(rec1[0], rec2[0])
        right = min(rec1[2], rec2[2])

        bottom = max(rec1[1], rec2[1])
        top = min(rec1[3], rec2[3])

        # Positive width AND positive height means overlap
        return left < right and bottom < top
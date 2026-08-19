from typing import List
from collections import defaultdict

class Solution:
    def maxNumberOfFamilies(self, n: int, reservedSeats: List[List[int]]) -> int:
        # bit i (0-indexed) represents seat i+1
        LEFT   = 0b0011110  # seats 2,3,4,5
        MIDDLE = 0b1111000  # wait, recompute carefully below
        
        # seats 2-5 -> bits 1,2,3,4
        LEFT   = (1<<1)|(1<<2)|(1<<3)|(1<<4)
        # seats 4-7 -> bits 3,4,5,6
        MIDDLE = (1<<3)|(1<<4)|(1<<5)|(1<<6)
        # seats 6-9 -> bits 5,6,7,8
        RIGHT  = (1<<5)|(1<<6)|(1<<7)|(1<<8)
        
        row_mask = defaultdict(int)
        for row, seat in reservedSeats:
            row_mask[row] |= (1 << (seat - 1))
        
        result = 2 * (n - len(row_mask))
        
        for mask in row_mask.values():
            if (mask & LEFT) == 0 and (mask & RIGHT) == 0:
                result += 2
            elif (mask & LEFT) == 0 or (mask & MIDDLE) == 0 or (mask & RIGHT) == 0:
                result += 1
        
        return result
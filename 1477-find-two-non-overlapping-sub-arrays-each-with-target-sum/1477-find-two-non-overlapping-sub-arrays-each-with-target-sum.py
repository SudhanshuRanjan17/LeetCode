class Solution:
    def minSumOfLengths(self, arr: list[int], target: int) -> int:
        n = len(arr)
        INF = n + 1

        # best[i] = minimum length of a valid subarray
        # completely within arr[0...i]
        best = [INF] * n

        left = 0
        current_sum = 0
        answer = INF

        for right in range(n):
            current_sum += arr[right]

            # Shrink the window if the sum exceeds target
            while current_sum > target:
                current_sum -= arr[left]
                left += 1

            # Check if current window has the target sum
            if current_sum == target:
                length = right - left + 1

                # Check for a previous non-overlapping subarray
                if left > 0 and best[left - 1] != INF:
                    answer = min(answer, length + best[left - 1])

                # Store the minimum valid length up to right
                if right == 0:
                    best[right] = length
                else:
                    best[right] = min(best[right - 1], length)

            else:
                # Carry forward the previous minimum
                if right > 0:
                    best[right] = best[right - 1]

        return answer if answer != INF else -1
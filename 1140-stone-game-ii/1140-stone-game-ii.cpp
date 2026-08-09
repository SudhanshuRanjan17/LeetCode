#include <vector>
#include <numeric>
#include <algorithm>

class Solution {
public:
    int stoneGameII(std::vector<int>& piles) {
        int n = piles.size();
        
        // Compute suffix sums where suffixSum[i] is the sum of piles[i...n-1]
        std::vector<int> suffixSum(n + 1, 0);
        for (int i = n - 1; i >= 0; --i) {
            suffixSum[i] = suffixSum[i + 1] + piles[i];
        }
        
        // memo[i][M] will store the result for dp(i, M)
        // Max value of M can reach n
        std::vector<std::vector<int>> memo(n, std::vector<int>(n + 1, 0));
        
        // Helper lambda function for recursion with memoization
        auto dp = [&](auto& self, int i, int M) -> int {
            // Base case: If remaining piles are <= 2 * M, pick all remaining stones
            if (i + 2 * M >= n) {
                return suffixSum[i];
            }
            
            if (memo[i][M] != 0) {
                return memo[i][M];
            }
            
            int maxStones = 0;
            for (int X = 1; X <= 2 * M; ++X) {
                int nextM = std::max(M, X);
                // Total stones from i minus what the next player optimal strategy yields
                int stones = suffixSum[i] - self(self, i + X, nextM);
                maxStones = std::max(maxStones, stones);
            }
            
            return memo[i][M] = maxStones;
        };
        
        return dp(dp, 0, 1);
    }
};
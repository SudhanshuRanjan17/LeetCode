class Solution {
public:
    int stoneGameV(vector<int>& stoneValue) {
        int n = stoneValue.size();
        
        // Prefix sum array to quickly calculate the sum of any subarray
        vector<int> prefixSum(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefixSum[i + 1] = prefixSum[i] + stoneValue[i];
        }

        // DP table for memoization initialized with -1
        vector<vector<int>> dp(n, vector<int>(n, -1));

        return solve(stoneValue, prefixSum, dp, 0, n - 1);
    }

private:
    int solve(const vector<int>& stoneValue, const vector<int>& prefixSum, vector<vector<int>>& dp, int left, int right) {
        // Base case: Only one stone left, score is 0
        if (left == right) return 0;
        
        // Return already computed result
        if (dp[left][right] != -1) return dp[left][right];

        int maxScore = 0;
        
        // Try all possible splits in the current row
        for (int i = left; i < right; ++i) {
            int sumLeft = prefixSum[i + 1] - prefixSum[left];
            int sumRight = prefixSum[right + 1] - prefixSum[i + 1];

            if (sumLeft < sumRight) {
                // Bob throws away the right part
                maxScore = max(maxScore, sumLeft + solve(stoneValue, prefixSum, dp, left, i));
            } else if (sumLeft > sumRight) {
                // Bob throws away the left part
                maxScore = max(maxScore, sumRight + solve(stoneValue, prefixSum, dp, i + 1, right));
            } else {
                // Alice gets to choose which part to keep when sums are equal
                maxScore = max(maxScore, sumLeft + max(solve(stoneValue, prefixSum, dp, left, i),
                                                       solve(stoneValue, prefixSum, dp, i + 1, right)));
            }
        }
        
        return dp[left][right] = maxScore;
    }
};
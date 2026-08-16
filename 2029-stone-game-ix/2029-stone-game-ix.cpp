class Solution {
public:
    bool stoneGameIX(vector<int>& stones) {
        vector<int> cnt(3, 0);
        
        // Count the frequencies of remainders
        for (int stone : stones) {
            cnt[stone % 3]++;
        }
        
        // If the count of numbers divisible by 3 is even
        if (cnt[0] % 2 == 0) {
            return cnt[1] > 0 && cnt[2] > 0;
        } 
        // If the count of numbers divisible by 3 is odd
        else {
            return abs(cnt[1] - cnt[2]) > 2;
        }
    }
};
class Solution {
public:
    int maxSubarrayLength(vector<int>& nums, int k) {
        unordered_map<int, int> counts;
        int left = 0, maxLength = 0;
        
        for (int right = 0; right < nums.size(); ++right) {
            counts[nums[right]]++;
            
            while (counts[nums[right]] > k) {
                counts[nums[left]]--;
                left++;
            }
            
            maxLength = max(maxLength, right - left + 1);
        }
        
        return maxLength;
    }
};
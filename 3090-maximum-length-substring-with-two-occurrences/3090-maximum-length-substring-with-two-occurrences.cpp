class Solution {
public:
    int maximumLengthSubstring(string s) {
        int max_len = 0;
        int left = 0;
        int freq[26] = {0};
        
        for (int right = 0; right < s.length(); ++right) {
            freq[s[right] - 'a']++;
            while (freq[s[right] - 'a'] > 2) {
                freq[s[left] - 'a']--;
                left++;
            }
            if (right - left + 1 > max_len) {
                max_len = right - left + 1;
            }
        }
        
        return max_len;
    }
};
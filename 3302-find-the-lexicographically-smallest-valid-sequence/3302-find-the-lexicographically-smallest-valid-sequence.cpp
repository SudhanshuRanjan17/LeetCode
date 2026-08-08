#include <vector>
#include <string>

class Solution {
public:
    std::vector<int> validSequence(std::string word1, std::string word2) {
        int n = word1.length();
        int m = word2.length();
        
        // suf[i] will store the maximum index in word2 that can be matched 
        // as a suffix starting from index i in word1.
        std::vector<int> suf(n + 1, 0);
        int j = m - 1;
        for (int i = n - 1; i >= 0; --i) {
            if (j >= 0 && word1[i] == word2[j]) {
                j--;
            }
            suf[i] = j + 1; // suf[i] indicates how many characters from the end of word2 are matched from index i onwards
        }
        
        std::vector<int> result;
        bool changed = false;
        int curr_word1_idx = 0;
        
        for (int i = 0; i < m; ++i) {
            // Try to find the next valid index in word1
            while (curr_word1_idx < n && 
                   (word1[curr_word1_idx] != word2[i]) && 
                   (changed || suf[curr_word1_idx + 1] > i + 1)) {
                curr_word1_idx++;
            }
            
            if (curr_word1_idx >= n) {
                return {}; // No valid sequence exists
            }
            
            if (word1[curr_word1_idx] == word2[i]) {
                result.push_back(curr_word1_idx);
                curr_word1_idx++;
            } else {
                // We must use our one allowed change here
                changed = true;
                result.push_back(curr_word1_idx);
                curr_word1_idx++;
            }
        }
        
        return result;
    }
};
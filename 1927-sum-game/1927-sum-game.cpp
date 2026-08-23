class Solution {
public:
    bool sumGame(string num) {
        int n = num.size();
        int mid = n / 2;

        int leftSum = 0;
        int rightSum = 0;
        int leftQ = 0;
        int rightQ = 0;

        // Process left half
        for (int i = 0; i < mid; i++) {
            if (num[i] == '?')
                leftQ++;
            else
                leftSum += num[i] - '0';
        }

        // Process right half
        for (int i = mid; i < n; i++) {
            if (num[i] == '?')
                rightQ++;
            else
                rightSum += num[i] - '0';
        }

        // Unequal number of '?' with odd difference
        if (abs(leftQ - rightQ) % 2 == 1)
            return true;

        // Bob can force equality
        int requiredDifference = 9 * (rightQ - leftQ) / 2;

        return leftSum - rightSum != requiredDifference;
    }
};
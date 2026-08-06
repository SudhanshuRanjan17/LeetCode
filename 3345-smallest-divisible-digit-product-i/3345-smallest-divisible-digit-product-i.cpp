class Solution {
public:
    int smallestNumber(int n, int t) {
        int current = n;
        while (true) {
            // Calculate the product of the digits of 'current'
            int product = 1;
            int temp = current;
            while (temp > 0) {
                product *= (temp % 10);
                temp /= 10;
            }
            
            // If the digit product is divisible by t, return current
            if (product % t == 0) {
                return current;
            }
            
            current++;
        }
    }
};
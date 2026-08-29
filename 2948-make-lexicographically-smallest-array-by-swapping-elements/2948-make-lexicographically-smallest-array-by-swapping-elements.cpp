class Solution {
public:
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        int n = nums.size();

        // Store {value, original_index}
        vector<pair<int, int>> arr;

        for (int i = 0; i < n; i++) {
            arr.push_back({nums[i], i});
        }

        // Sort by value
        sort(arr.begin(), arr.end());

        vector<int> ans(n);

        int i = 0;

        while (i < n) {
            int j = i;

            // Find one connected group.
            // Consecutive sorted values can belong to the same group
            // if their difference <= limit.
            while (j + 1 < n &&
                   arr[j + 1].first - arr[j].first <= limit) {
                j++;
            }

            // Extract original indices of this group
            vector<int> indices;

            for (int k = i; k <= j; k++) {
                indices.push_back(arr[k].second);
            }

            // Original positions must be sorted
            sort(indices.begin(), indices.end());

            // Values are already sorted
            int valueIndex = i;

            // Put smallest values into smallest indices
            for (int idx : indices) {
                ans[idx] = arr[valueIndex].first;
                valueIndex++;
            }

            i = j + 1;
        }

        return ans;
    }
};
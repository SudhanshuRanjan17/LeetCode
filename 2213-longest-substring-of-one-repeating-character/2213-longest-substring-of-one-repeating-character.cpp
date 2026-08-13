class Solution {
    struct Node {
        int max_len = 0;
        int left_len = 0;
        int right_len = 0;
        char left_char = 0;
        char right_char = 0;
    };

    int n;
    vector<Node> tree;

    Node combine(const Node& l, const Node& r, int left_len_total, int right_len_total) {
        Node res;
        res.left_char = l.left_char;
        res.right_char = r.right_char;

        res.left_len = l.left_len;
        if (l.left_len == left_len_total && l.left_char == r.left_char) {
            res.left_len = l.left_len + r.left_len;
        }

        res.right_len = r.right_len;
        if (r.right_len == right_len_total && r.right_char == l.right_char) {
            res.right_len = r.right_len + l.right_len;
        }

        res.max_len = max(l.max_len, r.max_len);
        if (l.right_char == r.left_char) {
            res.max_len = max(res.max_len, l.right_len + r.left_len);
        }

        return res;
    }

public:
    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices) {
        n = s.length();
        tree.resize(4 * n);
        
        auto build_tree = [&](auto& self, int node, int start, int end) -> void {
            if (start == end) {
                tree[node] = {1, 1, 1, s[start], s[start]};
                return;
            }
            int mid = (start + end) / 2;
            self(self, 2 * node, start, mid);
            self(self, 2 * node + 1, mid + 1, end);
            tree[node] = combine(tree[2 * node], tree[2 * node + 1], mid - start + 1, end - mid);
        };

        auto update_tree = [&](auto& self, int node, int start, int end, int idx, char val) -> void {
            if (start == end) {
                tree[node] = {1, 1, 1, val, val};
                return;
            }
            int mid = (start + end) / 2;
            if (idx <= mid)
                self(self, 2 * node, start, mid, idx, val);
            else
                self(self, 2 * node + 1, mid + 1, end, idx, val);
            tree[node] = combine(tree[2 * node], tree[2 * node + 1], mid - start + 1, end - mid);
        };

        build_tree(build_tree, 1, 0, n - 1);

        vector<int> ans;
        int k = queryIndices.size();
        for (int i = 0; i < k; ++i) {
            s[queryIndices[i]] = queryCharacters[i];
            update_tree(update_tree, 1, 0, n - 1, queryIndices[i], queryCharacters[i]);
            ans.push_back(tree[1].max_len);
        }

        return ans;
    }
};
struct Node {
    int max_len = 1;
    int pref_len = 1;
    int suff_len = 1;
    char pref_char = ' ';
    char suff_char = ' ';
};

class SegmentTree {
    int n;
    vector<Node> tree;

    Node merge(const Node& left, const Node& right, int left_len, int right_len) {
        Node res;
        res.pref_char = left.pref_char;
        res.suff_char = right.suff_char;

        // Base max length from either sub-interval
        res.max_len = max(left.max_len, right.max_len);

        // Check if middle boundary characters match
        if (left.suff_char == right.pref_char) {
            res.max_len = max(res.max_len, left.suff_len + right.pref_len);
        }

        // Calculate prefix length
        if (left.pref_len == left_len && left.pref_char == right.pref_char) {
            res.pref_len = left.pref_len + right.pref_len;
        } else {
            res.pref_len = left.pref_len;
        }

        // Calculate suffix length
        if (right.suff_len == right_len && right.suff_char == left.suff_char) {
            res.suff_len = right.suff_len + left.suff_len;
        } else {
            res.suff_len = right.suff_len;
        }

        return res;
    }

    void build(const string& s, int node, int start, int end) {
        if (start == end) {
            tree[node] = {1, 1, 1, s[start], s[start]};
            return;
        }
        int mid = start + (end - start) / 2;
        build(s, 2 * node, start, mid);
        build(s, 2 * node + 1, mid + 1, end);
        tree[node] = merge(tree[2 * node], tree[2 * node + 1], mid - start + 1, end - mid);
    }

    void update(int node, int start, int end, int idx, char val) {
        if (start == end) {
            tree[node] = {1, 1, 1, val, val};
            return;
        }
        int mid = start + (end - start) / 2;
        if (start <= idx && idx <= mid) {
            update(2 * node, start, mid, idx, val);
        } else {
            update(2 * node + 1, mid + 1, end, idx, val);
        }
        tree[node] = merge(tree[2 * node], tree[2 * node + 1], mid - start + 1, end - mid);
    }

public:
    SegmentTree(const string& s) {
        n = s.length();
        tree.resize(4 * n);
        build(s, 1, 0, n - 1);
    }

    void update(int idx, char val) {
        update(1, 0, n - 1, idx, val);
    }

    int getMax() const {
        return tree[1].max_len;
    }
};

class Solution {
public:
    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices) {
        int k = queryIndices.size();
        SegmentTree st(s);
        vector<int> result(k);

        for (int i = 0; i < k; ++i) {
            st.update(queryIndices[i], queryCharacters[i]);
            result[i] = st.getMax();
        }

        return result;
    }
};
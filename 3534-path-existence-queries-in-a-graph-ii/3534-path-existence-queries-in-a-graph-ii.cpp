class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        vector<pair<int, int>> sortedNodes(n);
        for (int i = 0; i < n; ++i) {
            sortedNodes[i] = {nums[i], i};
        }
        sort(sortedNodes.begin(), sortedNodes.end());

        // Map from original index to its position in the sorted array
        vector<int> posInSorted(n);
        for (int i = 0; i < n; ++i) {
            posInSorted[sortedNodes[i].second] = i;
        }

        // Compute the greedy next step (furthest right reachable node) for each sorted index
        // up[i][j] stores the 2^j-th jump from sorted index i
        int maxLog = log2(n) + 1;
        vector<vector<int>> up(n, vector<int>(maxLog, -1));

        for (int i = 0; i < n; ++i) {
            // Find the furthest node to the right within maxDiff
            auto it = upper_bound(sortedNodes.begin(), sortedNodes.end(), make_pair(sortedNodes[i].first + maxDiff, n));
            int targetIdx = distance(sortedNodes.begin(), it) - 1;
            
            if (targetIdx > i) {
                up[i][0] = targetIdx;
            } else {
                up[i][0] = -1; // No valid forward jump
            }
        }

        // Precompute binary lifting sparse table
        for (int j = 1; j < maxLog; ++j) {
            for (int i = 0; i < n; ++i) {
                if (up[i][j - 1] != -1) {
                    up[i][j] = up[up[i][j - 1]][j - 1];
                } else {
                    up[i][j] = -1;
                }
            }
        }

        vector<int> answer;
        answer.reserve(queries.size());

        for (const auto& q : queries) {
            int u = posInSorted[q[0]];
            int v = posInSorted[q[1]];

            if (u == v) {
                answer.push_back(0);
                continue;
            }

            // Ensure u has the smaller value
            if (u > v) swap(u, v);

            // Case 1: Directly reachable
            if (sortedNodes[v].first - sortedNodes[u].first <= maxDiff) {
                answer.push_back(1);
                continue;
            }

            // Case 2: Use binary lifting to jump as close to v as possible
            int steps = 0;
            for (int j = maxLog - 1; j >= 0; --j) {
                if (up[u][j] != -1 && sortedNodes[up[u][j]].first - sortedNodes[u].first > 0) {
                    // If the landing node still cannot reach v directly, we take the jump
                    if (sortedNodes[v].first - sortedNodes[up[u][j]].first > maxDiff) {
                        u = up[u][j];
                        steps += (1 << j);
                    }
                }
            }

            // After jumping optimally, check if one last step reaches v
            if (up[u][0] != -1 && sortedNodes[v].first - sortedNodes[up[u][0]].first <= maxDiff) {
                answer.push_back(steps + 2); // steps taken + 1 to reach up[u][0] + 1 to reach v
            } else {
                answer.push_back(-1);
            }
        }

        return answer;
    }
};
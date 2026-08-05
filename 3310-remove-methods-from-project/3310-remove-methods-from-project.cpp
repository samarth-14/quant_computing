class Solution {
public:
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        vector<vector<int>> adj(n);
        for (const auto& edge : invocations) {
            adj[edge[0]].push_back(edge[1]);
        }
        vector<bool> is_suspicious(n, false);
        queue<int> q;
        
        q.push(k);
        is_suspicious[k] = true;

        while (!q.empty()) {
            int curr = q.front();
            q.pop();

            for (int neighbor : adj[curr]) {
                if (!is_suspicious[neighbor]) {
                    is_suspicious[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }

        for (const auto& edge : invocations) {
            int u = edge[0], v = edge[1];
            if (!is_suspicious[u] && is_suspicious[v]) {
                vector<int> all_methods(n);
                iota(all_methods.begin(), all_methods.end(), 0);
                return all_methods;
            }
        }
        vector<int> result;
        for (int i = 0; i < n; ++i) {
            if (!is_suspicious[i]) {
                result.push_back(i);
            }
        }
        return result;
    }
};
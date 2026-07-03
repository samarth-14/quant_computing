class Solution {
public:
    int findMaxPathScore(vector<vector<int>>& edges, vector<bool>& online, long long k) {
        int n = online.size();
        
        // Build adjacency list and compute in-degrees for the full graph
        // to get a valid topological order of ALL nodes.
        vector<vector<pair<int, int>>> adj(n);
        vector<int> inDegree(n, 0);
        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int cost = edge[2];
            adj[u].push_back({v, cost});
        }
        
        // Perform Topological Sort
        for (int i = 0; i < n; ++i) {
            for (auto& edge : adj[i]) {
                inDegree[edge.first]++;
            }
        }
        
        queue<int> q;
        for (int i = 0; i < n; ++i) {
            if (inDegree[i] == 0) {
                q.push(i);
            }
        }
        
        vector<int> topoOrder;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            topoOrder.push_back(u);
            for (auto& edge : adj[u]) {
                int v = edge.first;
                if (--inDegree[v] == 0) {
                    q.push(v);
                }
            }
        }
        
        // Lambda function to check if a minimum edge cost of 'mid' is achievable
        auto check = [&](int mid) -> bool {
            // dp[i] stores the minimum path cost from node 0 to node i
            // Use -1 or a very large number (LLONG_MAX) to represent unreachability
            vector<long long> dp(n, -1);
            dp[0] = 0;
            
            for (int u : topoOrder) {
                if (dp[u] == -1 || !online[u]) continue;
                
                for (auto& edge : adj[u]) {
                    int v = edge.first;
                    int cost = edge.second;
                    
                    // Filter edges that have cost < mid or destination node is offline
                    if (cost < mid || !online[v]) continue;
                    
                    if (dp[v] == -1 || dp[u] + cost < dp[v]) {
                        dp[v] = dp[u] + cost;
                    }
                }
            }
            
            return dp[n - 1] != -1 && dp[n - 1] <= k;
        };
        
        // Binary search range for max min-edge cost
        int low = 0, high = 1e9, ans = -1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (check(mid)) {
                ans = mid;       // 'mid' is possible, try to look for a larger minimum
                low = mid + 1;
            } else {
                high = mid - 1;  // 'mid' is too high, lower the threshold
            }
        }
        
        return ans;
    }
};
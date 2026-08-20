class Solution {
public:
    bool iscycle(int src, vector<bool>& vis, vector<bool>& recpath, vector<vector<int>>& adj) {
        vis[src] = true;
        recpath[src] = true;

        for (int neighbor : adj[src]) {
            if (!vis[neighbor]) {
                if (iscycle(neighbor, vis, recpath, adj)) {
                    return true;
                }
            } else if (recpath[neighbor]) {
                return true;
            }
        }

        recpath[src] = false; 
        return false;
    }

    void topo(int src, vector<bool>& vis, std::stack<int>& s, vector<vector<int>>& adj) {
        vis[src] = true;

        for (int neighbor : adj[src]) {
            if (!vis[neighbor]) {
                topo(neighbor, vis, s, adj);
            }
        }

        s.push(src);
    }

    vector<int> findOrder(int n, vector<vector<int>>& prerequisites) {
        vector<vector<int>> adj(n);
        for (const auto& pre : prerequisites) {
            adj[pre[1]].push_back(pre[0]);
        }

        vector<bool> vis(n, false);
        vector<bool> recpath(n, false);
        vector<int> ans;
        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                if (iscycle(i, vis, recpath, adj)) {
                    return {}; 
                }
            }
        }

        stack<int> s;
        vis.assign(n, false);
        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                topo(i, vis, s, adj);
            }
        }

        while (!s.empty()) {
            ans.push_back(s.top());
            s.pop(); 
        }

        return ans;
    }
};
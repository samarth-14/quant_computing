class Solution {
public:
    int maximumSafenessFactor(vector<vector<int>>& grid) {
        int n = grid.size();

        vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
        queue<pair<int, int>> q;

        // Push all thief cells into the queue
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    dist[i][j] = 0;
                    q.push({i, j});
                }
            }
        }

        // Multi-source BFS to compute distance to nearest thief
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            for (int k = 0; k < 4; k++) {
                int nr = r + dr[k];
                int nc = c + dc[k];

                if (nr >= 0 && nr < n && nc >= 0 && nc < n &&
                    dist[nr][nc] == INT_MAX) {
                    dist[nr][nc] = dist[r][c] + 1;
                    q.push({nr, nc});
                }
            }
        }

        auto canReach = [&](int safe) {
            if (dist[0][0] < safe) return false;

            vector<vector<bool>> vis(n, vector<bool>(n, false));
            queue<pair<int, int>> bfs;
            bfs.push({0, 0});
            vis[0][0] = true;

            while (!bfs.empty()) {
                auto [r, c] = bfs.front();
                bfs.pop();

                if (r == n - 1 && c == n - 1)
                    return true;

                for (int k = 0; k < 4; k++) {
                    int nr = r + dr[k];
                    int nc = c + dc[k];

                    if (nr >= 0 && nr < n &&
                        nc >= 0 && nc < n &&
                        !vis[nr][nc] &&
                        dist[nr][nc] >= safe) {
                        vis[nr][nc] = true;
                        bfs.push({nr, nc});
                    }
                }
            }

            return false;
        };

        int low = 0, high = 2 * n, ans = 0;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (canReach(mid)) {
                ans = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return ans;
    }
};
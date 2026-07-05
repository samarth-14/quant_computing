class Solution {
public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
        int n = board.size();
        int MOD = 1e9 + 7;
        vector<vector<pair<int, int>>> dp(n, vector<pair<int, int>>(n, {-1, 0}));
        dp[n-1][n-1] = {0, 1};
        int dirs[3][2] = {{1, 0}, {0, 1}, {1, 1}};
        for (int i = n - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                if (i == n - 1 && j == n - 1) continue;
                if (board[i][j] == 'X') continue;
                
                int max_prev_score = -1;
                int paths_sum = 0;
                for (auto& d : dirs) {
                    int ni = i + d[0];
                    int nj = j + d[1];
                    
                    if (ni < n && nj < n && dp[ni][nj].first != -1) {
                        if (dp[ni][nj].first > max_prev_score) {
                            max_prev_score = dp[ni][nj].first;
                            paths_sum = dp[ni][nj].second;
                        } else if (dp[ni][nj].first == max_prev_score) {
                            paths_sum = (paths_sum + dp[ni][nj].second) % MOD;
                        }
                    }
                }
                if (max_prev_score != -1) {
                    int current_val = (board[i][j] == 'E') ? 0 : (board[i][j] - '0');
                    dp[i][j] = {max_prev_score + current_val, paths_sum};
                }
            }
        }
        if (dp[0][0].first == -1) {
            return {0, 0};
        }
        
        return {dp[0][0].first, dp[0][0].second};
    }
};
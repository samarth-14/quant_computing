#include <vector>
#include <numeric>
#include <algorithm>

class Solution {
public:
    int stoneGameV(std::vector<int>& stoneValue) {
        int n = stoneValue.size();
        
        // Build prefix sum array for fast range sum queries in O(1)
        std::vector<int> prefix(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefix[i + 1] = prefix[i] + stoneValue[i];
        }
        
        auto get_sum = [&](int i, int j) {
            return prefix[j + 1] - prefix[i];
        };

        // dp[i][j] stores the maximum score Alice can get from subarray stoneValue[i...j]
        std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));

        // Fill DP table based on interval length
        for (int len = 2; len <= n; ++len) {
            for (int i = 0; i <= n - len; ++i) {
                int j = i + len - 1;
                
                for (int k = i; k < j; ++k) {
                    int left_sum = get_sum(i, k);
                    int right_sum = get_sum(k + 1, j);
                    
                    if (left_sum < right_sum) {
                        dp[i][j] = std::max(dp[i][j], left_sum + dp[i][k]);
                    } else if (right_sum < left_sum) {
                        dp[i][j] = std::max(dp[i][j], right_sum + dp[k + 1][j]);
                    } else {
                        // Equal sums: choose the best path
                        dp[i][j] = std::max({
                            dp[i][j], 
                            left_sum + dp[i][k], 
                            right_sum + dp[k + 1][j]
                        });
                    }
                }
            }
        }

        return dp[0][n - 1];
    }
};
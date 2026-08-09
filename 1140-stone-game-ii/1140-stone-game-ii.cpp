
class Solution {
public:
    int stoneGameII(vector<int>& piles) {
        int n = piles.size();
        vector<vector<int>> dp(n, vector<int>(n + 1, 0));
        vector<int> suffixSum(n, 0);

        suffixSum[n - 1] = piles[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            suffixSum[i] = suffixSum[i + 1] + piles[i];
        }

        return helper(0, 1, piles, suffixSum, dp);
    }

private:
    int helper(int i, int M, const vector<int>& piles, const vector<int>& suffixSum, vector<vector<int>>& dp) {
        int n = piles.size();
        
        // If remaining piles are less than or equal to 2 * M, take them all
        if (i + 2 * M >= n) {
            return suffixSum[i];
        }
        
        if (dp[i][M] != 0) {
            return dp[i][M];
        }

        int minOpponentStones = INT_MAX;
        
        for (int X = 1; X <= 2 * M; ++X) {
            int nextM = max(M, X);
            minOpponentStones = min(minOpponentStones, helper(i + X, nextM, piles, suffixSum, dp));
        }

        dp[i][M] = suffixSum[i] - minOpponentStones;
        return dp[i][M];
    }
};
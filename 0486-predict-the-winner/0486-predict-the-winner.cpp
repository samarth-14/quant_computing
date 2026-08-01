class Solution {
public:
    bool predictTheWinner(vector<int>& nums) {
        int n =nums.size();
        vector<int> dp=nums;
        for(int l =2;l<=n;l++){
            for(int i =0;i<=n-l;i++){
                int j=i+l-1;
                dp[i] = max(nums[i] - dp[i + 1], nums[j] - dp[i]);
            }
        }
        return dp[0]>=0;
    }
};
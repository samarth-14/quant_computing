class Solution {
public:
    string stoneGameIII(vector<int>& stoneValue) {
        int n =stoneValue.size();
        vector<int>dp(n+1,0);
        for(int i =n-1;i>=0;i--){
            int t=stoneValue[i]-dp[i+1];
            int t2=-1e9;
            if(i+1<n){
                t2=stoneValue[i]+stoneValue[i+1]-dp[i+2];
            }
            int t3=-1e9;
            if(i+2<n){
                t3=stoneValue[i]+stoneValue[i+1]+stoneValue[i+2]-dp[i+3];
            }
            dp[i]=max({t,t2,t3});
        }
        if (dp[0] > 0) return "Alice";
        if (dp[0] <0) return "Bob";
        return "Tie";
    }
};
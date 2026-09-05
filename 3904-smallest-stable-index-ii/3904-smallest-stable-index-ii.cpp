class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n =nums.size();
        if(n==0)return -1;
        vector<int>m(n);
        vector<int>s(n);
        m[0]=nums[0];
        for(int i =1;i<n;i++){
            m[i]=max(m[i-1],nums[i]);
        }
        s[n-1]=nums[n-1];
        for(int i=n-2;i>=0;i--){
            s[i]=min(s[i+1],nums[i]);
        }
        for(int i =0;i<n;i++){
            if(m[i]-s[i]<=k){
                return i;
            }
        }
        return -1;
    }
};
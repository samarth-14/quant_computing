class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n =nums.size();
        vector<int> m(n);
        m[n-1]=nums[n-1];
        for(int i =n-2;i>=0;i--){
            m[i]=min(nums[i],m[i+1]);
        }
        int c=0;
        for(int i=0;i<n;i++){
            c=max(c,nums[i]);
            if(c-m[i]<=k){
                return i;
            }
        }
        return -1;
    }
};
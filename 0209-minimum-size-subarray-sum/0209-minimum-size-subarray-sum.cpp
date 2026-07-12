class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n=nums.size();
        int l=0;
        int sum=0;
        int len=INT_MAX;
        for(int i =0;i<n;i++){
            sum+=nums[i];
            while(sum>=target){
                len=min(len,i-l+1);
                sum-=nums[l];
                l++;
            }
        }
        return (len==INT_MAX) ? 0:len;
    }
};
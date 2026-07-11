class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        if(k<=1){
            return 0;
        }
        int n = nums.size();
        int count =0;
        int l=0;
        int prod=1;
        for(int i=0;i<n;i++){
            prod*=nums[i];
            while(prod>=k){
                prod/=nums[l];
                l++;
            }
            count+=i-l+1;
        }
        return count;
    }
};
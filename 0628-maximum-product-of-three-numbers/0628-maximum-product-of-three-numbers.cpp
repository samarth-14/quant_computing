class Solution {
public:
    int maximumProduct(vector<int>& nums) {
        int n =nums.size();
        sort(nums.begin(),nums.end());
        int p=nums[n-1] * nums[n-2] * nums[n-3];;
        int q=nums[0] * nums[1] * nums[n-1];
        int r=nums[n-1]*nums[n-2]*nums[0];
        int m=max(p,q);
        int s=max(r,m);
        return s;
    }
};
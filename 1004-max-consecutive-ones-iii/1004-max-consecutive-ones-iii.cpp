class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int l=0;
        int count0=0;
        int n=nums.size();
        for(int i =0;i<n;i++){
            if(nums[i]==0){
                count0++;
            }    
                if(count0>k){
                    if(nums[l]==0){
                        count0--;
                    }
                    l++;
                }
        }
        return n-l;
    }
};
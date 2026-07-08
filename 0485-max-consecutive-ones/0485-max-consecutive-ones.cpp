class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int ans=0;
        int count=0;
        int j=0;
        int n =nums.size();
        while(j<n){
            if(nums[j]==1){
                j++;
                count++;
            }else{
                j++;
                ans=max(ans,count);
                count =0;
            }
        }
        return max(ans,count);
    }
};
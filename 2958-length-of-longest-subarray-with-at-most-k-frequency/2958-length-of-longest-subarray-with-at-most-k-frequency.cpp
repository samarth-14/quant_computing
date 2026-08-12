class Solution {
public:
    int maxSubarrayLength(vector<int>& nums, int k) {
        unordered_map<int,int>mpp;
        for(int i=0;i<nums.size();i++){
            mpp[nums[i]]=0;
        }
        int left=0;
        int max_length=0;
        for(int i=0;i<nums.size();i++){
            mpp[nums[i]]++;
            while(mpp[nums[i]]>k){
                mpp[nums[left]]--;
                left++;
            }
            max_length=max(max_length,i-left+1);
        }
        return max_length;
    }
};
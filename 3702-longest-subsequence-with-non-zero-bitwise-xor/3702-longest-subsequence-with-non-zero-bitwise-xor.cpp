class Solution {
public:
    int longestSubsequence(vector<int>& nums) {
        int T=0;
        int z=false;
        for(int num:nums){
            T^=num;
            if(num!=0){
                z=true;
            }
        }
        if(!z){
            return 0;
        }
        if(T!=0){
            return nums.size();
        }
        return nums.size()-1;
    }
};
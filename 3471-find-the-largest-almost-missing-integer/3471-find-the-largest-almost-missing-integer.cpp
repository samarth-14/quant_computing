class Solution {
public:
    int largestInteger(vector<int>& nums, int k) {
        int n =nums.size();
        unordered_map<int,int>freq;
        for(int num:nums){
            freq[num]++;
        }
        if(k==1){
            int val=-1;
            for(auto&[vale,count]:freq){
                if(count==1){
                    val=max(val,vale);
                }
            }
            return val;
        }
        if(k==n){
            int val=-1;
            for(int num:nums){
                val=max(val,num);
            }
            return val;
        }
        int ans=-1;
        if(freq[nums[0]]==1){
            ans=max(ans,nums[0]);
        }
        if(freq[nums[n-1]]==1){
            ans=max(ans,nums[n-1]);
        }
        return ans;
    }
};
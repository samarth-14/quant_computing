class Solution {
public:
    vector<int> findMissingElements(vector<int>& nums) {
        int m =*min_element(nums.begin(),nums.end());
        int n=*max_element(nums.begin(),nums.end());
        unordered_set<int> p(nums.begin(),nums.end());
        vector<int>ans;
        for(int i =m;i<=n;i++){
            if(p.find(i)==p.end()){
                ans.push_back(i);
            }
        }
        return ans;
    }
};
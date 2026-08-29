class Solution {
public:
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        int n =nums.size();
        vector<pair<int,int>>p(n);
        for(int i =0;i<n;i++){
            p[i]={nums[i],i};
        }
        sort(p.begin(),p.end());
        vector<int>ans(n);
        int i =0;
        while(i<n){
            int j=i;
            while(j+1<n&&p[j+1].first-p[j].first<=limit){
                j++;
            }
            vector<int>indices;
            for(int k =i;k<=j;k++){
                indices.push_back(p[k].second);
            }
            sort(indices.begin(),indices.end());
            for(int k=0;k<indices.size();k++){
                ans[indices[k]]=p[i+k].first;
            }
            i=j+1;
        }    
        return ans;
    }
};
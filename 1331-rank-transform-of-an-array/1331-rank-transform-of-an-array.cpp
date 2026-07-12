class Solution {
public:
    vector<int> arrayRankTransform(vector<int>& arr) {
        vector<int> sortedar=arr;
        sort(sortedar.begin(),sortedar.end());
        unordered_map<int,int>mp;
        int rank=1;
        for(int n:sortedar){
            if(mp.find(n)==mp.end()){
                mp[n]=rank;
                rank++;
            }
        }
        for(int i=0;i<arr.size();i++){
            arr[i]=mp[arr[i]];
        }
        return arr;
    }
};
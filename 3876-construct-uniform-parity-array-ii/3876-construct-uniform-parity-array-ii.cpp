class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
       int n =nums1[0];
       bool odd=false;
       for(int x:nums1){
        if(x<n){
            n=x;
        }
        if(x%2!=0){
            odd=true;
        }
       }
       if(!odd) return true;
       return n%2!=0;
    }
};
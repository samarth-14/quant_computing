class Solution {
public:
    long long gcdSum(vector<int>& nums) {
        int n =nums.size();
        vector<long long>pref(n);
        long long curr=0;
        for(int i=0;i<n;i++){
            curr=max(curr,(long long)nums[i]);
            pref[i]=gcd((long long)nums[i],curr);
        }
        sort(pref.begin(),pref.end());
        long long sum=0;
        int l=0;
        int r=n-1;
        while(l<r){
            sum+=gcd(pref[l],pref[r]);
            l++;
            r--;
        }
        return sum;
    }
};
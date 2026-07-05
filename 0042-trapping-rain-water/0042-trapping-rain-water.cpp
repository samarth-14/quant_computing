class Solution {
public:
    int trap(vector<int>& height) {
        int n =height.size();
        if(n<=2)return 0;
        int l=0;
        int r=n-1;
        int w=0;
        int l1=height[l],r1=height[r];
        while(l<r){
            if(l1<r1){
                l++;
                l1=max(l1,height[l]);
                w+=l1-height[l];
            }else{
                r--;
                r1=max(r1,height[r]);
                w+=r1-height[r];
            }
        }
        return w;
    }
};
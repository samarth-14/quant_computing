class Solution {
public:
    int maxProduct(int n) {
        int a=0,m=0;
        while(n>0){
            int d=n%10;
            n/=10;
            if(d>a){
                m=a;
                a=d;
            }else if(d>m){
                m=d;
            }
        }
        return a*m;
    }
};
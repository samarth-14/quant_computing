class Solution {
public:
    bool isPalindrome(int x) {
        if(x<0||x%10==0&&x!=0){
            return false;
        }
        int h=0;
        while(x>h){
            h=h*10+x%10;
            x/=10;
        }
       return x==h||x==h/10;
    }
};
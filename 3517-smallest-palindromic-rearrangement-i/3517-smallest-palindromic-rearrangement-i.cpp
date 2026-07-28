class Solution {
public:
    string smallestPalindrome(string s) {
        int n=s.length();
        string h=s.substr(0,n/2);
        sort(h.begin(),h.end());
        string r=h;
        reverse(r.begin(),r.end());
        if(n%2==0){
            return h+r;
        }else{
            return h+s[n/2]+r;
        }
    }
};
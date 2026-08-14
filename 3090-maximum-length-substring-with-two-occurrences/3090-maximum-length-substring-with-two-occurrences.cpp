class Solution {
public:
    int maximumLengthSubstring(string s) {
        vector<int> count(26, 0);
        int len=0;
        int l=0;
        for(int r=0;r<s.length();r++){
            count[s[r]-'a']++;
            while(count[s[r]-'a']>2){
                count[s[l]-'a']--;
                l++;
            }
            len=max(len,r-l+1);
        }
        return len;
    }
};
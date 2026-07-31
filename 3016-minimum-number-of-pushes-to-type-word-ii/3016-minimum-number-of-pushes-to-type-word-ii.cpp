class Solution {
public:
    int minimumPushes(string word) {
        vector<int> f(26,0);
        for(char c:word){
            f[c-'a']++;
        }
        sort(f.rbegin(),f.rend());
        int t=0;
        for(int i =0;i<26;i++){
            if(f[i]==0)break;
            int p=(i/8)+1;
            t+=f[i]*p;
        }
        return t;
    }
};
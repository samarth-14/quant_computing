class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {
        int total=0;
        vector<int> zero;
        int n=s.length();
        int i =0;
        while(i<n){
            if(s[i]=='1'){
                total++;
                i++;
            }else{
                int su=i;
                while(i<n&&s[i]=='0'){
                    i++;
                }
                zero.push_back(i-su);
            }
        }
        int gain=0;
        for(size_t k=0;k+1<zero.size();k++){
            gain=max(gain,zero[k]+zero[k+1]);
        }
        return total+gain;
    }
};
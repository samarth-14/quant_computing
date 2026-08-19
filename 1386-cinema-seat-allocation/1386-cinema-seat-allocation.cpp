class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        unordered_map<int,int>mask;
        for(const auto& seat:reservedSeats){
            int row=seat[0];
            int col=seat[1];
            if(col>=2&&col<=9){
                mask[row]|=(1<<(col-2));
            }
        }
        int g=(n-mask.size())*2;
        int l=15;
        int m=60;
        int r=240;
        for(const auto& [row,maske]:mask){
            bool lf=(maske &l)==0;
            bool rf =(maske&r)==0;
            bool mf=(maske &m)==0;
            if(lf&&rf){
                g+=2;
            }else if(lf||rf||mf){
                g+=1;
            }
        }
        return g;
    }
};
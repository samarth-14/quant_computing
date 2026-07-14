class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        int n=stones.size();
        while(stones.size()>1){
            sort(stones.begin(),stones.end(),greater<int>());
            int y =stones[0];
            int x=stones[1];
            stones.erase(stones.begin(),stones.begin()+2);
            if(x!=y){
                stones.push_back(y-x);
            }
        }
        return stones.empty()?0:stones[0];
    }
};
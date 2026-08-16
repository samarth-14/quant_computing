class Solution {
public:
    bool stoneGameIX(vector<int>& stones) {
        vector<int> count(3, 0);
        for (int stone : stones) {
            count[stone % 3]++;
        }
        
        int c0 = count[0], c1 = count[1], c2 = count[2];
        
        if (c0 % 2 == 0) {
            return c1 >= 1 && c2 >= 1;
        } else {
            return abs(c1 - c2) > 2;
        }
    }
};
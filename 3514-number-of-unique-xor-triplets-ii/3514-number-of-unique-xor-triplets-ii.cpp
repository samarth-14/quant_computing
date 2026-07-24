class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        int n = nums.size();
        int maxEl = 0;
        for (int num : nums) {
            maxEl = max(maxEl, num);
        }
        int T = 1;
        while (T <= maxEl) {
            T <<= 1;
        }
        
        vector<bool> pairXor(T, false);
        vector<bool> tripletXor(T, false);
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                pairXor[nums[i] ^ nums[j]] = true;
            }
        }
        for (int x = 0; x < T; ++x) {
            if (pairXor[x]) {
                for (int num : nums) {
                    tripletXor[x ^ num] = true;
                }
            }
        }
        int count = 0;
        for (int i = 0; i < T; ++i) {
            if (tripletXor[i]) {
                count++;
            }
        }
        
        return count;
    }
};
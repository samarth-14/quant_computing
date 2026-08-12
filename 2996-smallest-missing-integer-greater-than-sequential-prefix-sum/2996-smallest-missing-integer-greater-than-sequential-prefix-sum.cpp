class Solution {
public:
    int missingInteger(vector<int>& nums) {
        int sum = nums[0];
        for (size_t i = 1; i < nums.size(); ++i) {
            if (nums[i] == nums[i - 1] + 1) {
                sum += nums[i];
            } else {
                break;
            }
        }
        
        // Step 2: Store elements in a hash set for quick lookup
        std::unordered_set<int> st(nums.begin(), nums.end());
        
        // Step 3: Find smallest integer >= sum that is missing from nums
        while (st.count(sum)) {
            sum++;
        }
        
        return sum;
    }
};
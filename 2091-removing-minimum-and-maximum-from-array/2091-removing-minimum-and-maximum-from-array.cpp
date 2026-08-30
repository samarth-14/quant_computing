class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        int n = nums.size();
        
        // Find indices of minimum and maximum elements
        int min_idx = 0, max_idx = 0;
        for (int k = 0; k < n; ++k) {
            if (nums[k] < nums[min_idx]) min_idx = k;
            if (nums[k] > nums[max_idx]) max_idx = k;
        }
        
        // Ensure i is the smaller index and j is the larger index
        int i = std::min(min_idx, max_idx);
        int j = std::max(min_idx, max_idx);
        
        // Scenario 1: Remove both from front -> j + 1
        // Scenario 2: Remove both from back  -> n - i
        // Scenario 3: Remove i from front and j from back -> (i + 1) + (n - j)
        return std::min({j + 1, n - i, i + 1 + n - j});
    }
};
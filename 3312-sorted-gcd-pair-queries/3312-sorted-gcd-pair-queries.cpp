class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        int max_val = *max_element(nums.begin(), nums.end());
        
        vector<long long> freq(max_val + 1, 0);
        for (int num : nums) {
            freq[num]++;
        }
        vector<long long> gcd_count(max_val + 1, 0);
        for (int i = max_val; i >= 1; --i) {
            long long count_multiples = 0;
            for (int j = i; j <= max_val; j += i) {
                count_multiples += freq[j];
            }
            
            long long total_pairs = (count_multiples * (count_multiples - 1)) / 2;
            
            for (int j = 2 * i; j <= max_val; j += i) {
                total_pairs -= gcd_count[j];
            }
            
            gcd_count[i] = total_pairs;
        }
        vector<long long> prefix_sums(max_val + 1, 0);
        for (int i = 1; i <= max_val; ++i) {
            prefix_sums[i] = prefix_sums[i - 1] + gcd_count[i];
        }
        vector<int> ans;
        ans.reserve(queries.size());
        for (long long q : queries) {
            auto it = upper_bound(prefix_sums.begin(), prefix_sums.end(), q);
            int gcd_val = distance(prefix_sums.begin(), it);
            ans.push_back(gcd_val);
        }
        
        return ans;
    }
};
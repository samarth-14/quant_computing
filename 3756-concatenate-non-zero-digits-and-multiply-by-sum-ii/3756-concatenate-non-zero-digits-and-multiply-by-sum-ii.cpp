class Solution {
public:
    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        int m = s.length();
        long long MOD = 1e9 + 7;
        
        // Prefix sums for the sum of digits
        vector<long long> pref_sum(m + 1, 0);
        for (int i = 0; i < m; ++i) {
            pref_sum[i + 1] = pref_sum[i] + (s[i] - '0');
        }
        
        // Extract non-zero digits and track their original indices
        vector<int> nz_digits;
        vector<int> nz_positions;
        for (int i = 0; i < m; ++i) {
            if (s[i] != '0') {
                nz_digits.push_back(s[i] - '0');
                nz_positions.push_back(i);
            }
        }
        
        int k = nz_digits.size();
        // Compute prefix hashes for the non-zero concatenated integer
        vector<long long> P(k + 1, 0);
        for (int i = 0; i < k; ++i) {
            P[i + 1] = (P[i] * 10 + nz_digits[i]) % MOD;
        }
        
        // Precompute powers of 10
        vector<long long> pow10(k + 1, 1);
        for (int i = 1; i <= k; ++i) {
            pow10[i] = (pow10[i - 1] * 10) % MOD;
        }
        
        vector<int> answer;
        answer.reserve(queries.size());
        
        for (const auto& q : queries) {
            int l = q[0], r = q[1];
            
            // Find the range of non-zero indices that fit within [l, r]
            auto it1 = lower_bound(nz_positions.begin(), nz_positions.end(), l);
            auto it2 = upper_bound(nz_positions.begin(), nz_positions.end(), r);
            
            if (it1 == it2) {
                // No non-zero digits in this range
                answer.push_back(0);
            } else {
                int idx1 = distance(nz_positions.begin(), it1);
                int idx2 = distance(nz_positions.begin(), it2) - 1;
                int len = idx2 - idx1 + 1;
                
                // Extract x % MOD
                long long x = (P[idx2 + 1] - (P[idx1] * pow10[len]) % MOD + MOD) % MOD;
                
                // Extract digit sum
                long long current_sum = pref_sum[r + 1] - pref_sum[l];
                
                // Compute final answer for the query
                long long ans = (x * (current_sum % MOD)) % MOD;
                answer.push_back(ans);
            }
        }
        
        return answer;
    }
};
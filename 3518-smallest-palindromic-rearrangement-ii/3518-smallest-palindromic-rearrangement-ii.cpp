#include <string>
#include <vector>
#include <numeric>

using namespace std;

class Solution {
private:
    // Computes nCr capped at 'cap' to prevent overflow
    long long nCr(int n, int r, long long cap) {
        if (r < 0 || r > n) return 0;
        if (r == 0 || r == n) return 1;
        if (r > n / 2) r = n - r;
        
        long long res = 1;
        for (int i = 1; i <= r; ++i) {
            res = res * (n - r + i) / i;
            if (res > cap) return cap;
        }
        return res;
    }

    // Computes total distinct permutations of remaining multiset, capped at 'cap'
    long long countPermutations(const vector<int>& counts, int N, long long cap) {
        long long total = 1;
        int rem = N;
        for (int c : counts) {
            if (c == 0) continue;
            total *= nCr(rem, c, cap);
            if (total >= cap) return cap;
            rem -= c;
        }
        return total;
    }

public:
    string smallestPalindrome(string s, int k) {
        int n = s.length();
        int M = n / 2;
        
        // Count frequencies of characters in string s
        vector<int> full_counts(26, 0);
        for (char ch : s) {
            full_counts[ch - 'a']++;
        }
        
        // Half counts for building the first half
        vector<int> counts(26, 0);
        char mid_char = 0;
        
        for (int i = 0; i < 26; ++i) {
            counts[i] = full_counts[i] / 2;
            if (full_counts[i] % 2 != 0) {
                mid_char = 'a' + i;
            }
        }
        
        // Initial permutation count for the first half
        long long P = countPermutations(counts, M, k + 1);
        if (P < k) return ""; // Fewer than k distinct palindromic permutations
        
        string half = "";
        half.reserve(M);
        
        long long current_k = k;
        
        for (int i = 0; i < M; ++i) {
            int L = M - i; // Remaining length
            
            for (int c = 0; c < 26; ++c) {
                if (counts[c] == 0) continue;
                
                long long Pc;
                if (P >= current_k + 1) {
                    counts[c]--;
                    Pc = countPermutations(counts, L - 1, current_k + 1);
                    counts[c]++;
                } else {
                    Pc = P * counts[c] / L;
                }
                
                if (current_k <= Pc) {
                    half.push_back('a' + c);
                    counts[c]--;
                    P = Pc;
                    break;
                } else {
                    current_k -= Pc;
                }
            }
        }
        
        // Construct full palindromic string from the first half
        string result = half;
        if (n % 2 != 0) {
            result.push_back(mid_char);
        }
        for (int i = M - 1; i >= 0; --i) {
            result.push_back(half[i]);
        }
        
        return result;
    }
};
class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        int n = s.length();
        vector<int> freq(26, 0);
        for (char c : s) freq[c - 'a']++;

        int odd_cnt = 0;
        char mid_char = 0;
        vector<int> half_freq(26, 0);

        for (int i = 0; i < 26; ++i) {
            if (freq[i] % 2 != 0) {
                odd_cnt++;
                mid_char = 'a' + i;
            }
            half_freq[i] = freq[i] / 2;
        }

        if (odd_cnt > 1) return "";

        int m = n / 2;
        string best_half = "";
        bool found = false;

        // Try prefix lengths of the half palindrome matching target from m down to 0
        for (int k = m; k >= 0; --k) {
            // Check matching prefix up to k-1
            vector<int> rem_freq = half_freq;
            string pref = "";
            bool valid_prefix = true;

            for (int i = 0; i < k; ++i) {
                if (rem_freq[target[i] - 'a'] > 0) {
                    pref += target[i];
                    rem_freq[target[i] - 'a']--;
                } else {
                    valid_prefix = false;
                    break;
                }
            }

            if (!valid_prefix) continue;

            // If k == m, check if exact prefix match works with middle character / reverse
            if (k == m) {
                string full = pref;
                if (n % 2 != 0) full += mid_char;
                string rev = pref;
                reverse(rev.begin(), rev.end());
                full += rev;

                if (full > target) {
                    return full;
                }
                continue;
            }

            // Try picking a character at position k strictly greater than target[k]
            for (int c = target[k] - 'a' + 1; c < 26; ++c) {
                if (rem_freq[c] > 0) {
                    rem_freq[c]--;
                    string curr = pref + (char)('a' + c);

                    // Fill remaining half greedily with smallest available characters
                    for (int j = 0; j < 26; ++j) {
                        while (rem_freq[j] > 0) {
                            curr += (char)('a' + j);
                            rem_freq[j]--;
                        }
                    }

                    string full = curr;
                    if (n % 2 != 0) full += mid_char;
                    string rev = curr;
                    reverse(rev.begin(), rev.end());
                    full += rev;

                    if (full > target) {
                        return full;
                    }

                    rem_freq[c]++; // Backtrack for next character test
                }
            }
        }

        return "";
    }
};
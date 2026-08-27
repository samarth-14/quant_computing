class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.length();
        vector<int> count(26, 0);
        for (char c : s) {
            count[c - 'a']++;
        }

        // Try to match target[0...i-1] exactly, and bump target[i]
        for (int i = n - 1; i >= 0; i--) {
            vector<int> temp_count = count;
            bool valid_prefix = true;

            // Check if target[0...i-1] can be formed by available characters
            for (int j = 0; j < i; j++) {
                if (--temp_count[target[j] - 'a'] < 0) {
                    valid_prefix = false;
                    break;
                }
            }

            if (!valid_prefix) continue;

            // Find the smallest character strictly greater than target[i]
            int bump_char = -1;
            for (int c = (target[i] - 'a') + 1; c < 26; c++) {
                if (temp_count[c] > 0) {
                    bump_char = c;
                    break;
                }
            }

            // If a valid bump character exists, construct the result
            if (bump_char != -1) {
                string result = target.substr(0, i);
                result += (char)('a' + bump_char);
                temp_count[bump_char]--;

                // Append remaining characters in ascending order
                for (int c = 0; c < 26; c++) {
                    while (temp_count[c] > 0) {
                        result += (char)('a' + c);
                        temp_count[c]--;
                    }
                }
                return result;
            }
        }

        return "";
    }
};
class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.length();
        int m = word2.length();

        // last_pos[j] stores the largest index in word1 that can match word2[j]
        // when matching word2[j...m-1] backwards from the end of word1.
        vector<int> last_pos(m, -1);
        
        int ptr = n - 1;
        for (int j = m - 1; j >= 0; --j) {
            while (ptr >= 0 && word1[ptr] != word2[j]) {
                ptr--;
            }
            last_pos[j] = ptr;
            ptr--; // move to the left for the next character
        }

        vector<int> result;
        bool used_mismatch = false;
        int word1_idx = 0;

        for (int i = 0; i < m; ++i) {
            while (word1_idx < n) {
                // Case 1: Exact match
                if (word1[word1_idx] == word2[i]) {
                    result.push_back(word1_idx);
                    word1_idx++;
                    break;
                }

                // Case 2: Mismatch occurs, and we haven't used our single allowed change yet
                if (!used_mismatch) {
                    // Check if the remaining suffix word2[i+1...] can be matched in word1[word1_idx+1...]
                    bool can_finish = (i == m - 1) || (last_pos[i + 1] > word1_idx);
                    
                    if (can_finish) {
                        used_mismatch = true;
                        result.push_back(word1_idx);
                        word1_idx++;
                        break;
                    }
                }

                // If no match and cannot use mismatch here, try the next index in word1
                word1_idx++;
            }

            // If we couldn't find a valid index for word2[i], no solution exists
            if (result.size() != i + 1) {
                return {};
            }
        }

        return result;
    }
};
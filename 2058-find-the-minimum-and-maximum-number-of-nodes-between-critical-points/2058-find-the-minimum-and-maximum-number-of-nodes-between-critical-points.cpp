/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        if (!head || !head->next || !head->next->next) {
            return {-1, -1};
        }

        ListNode* prev = head;
        ListNode* curr = head->next;
        
        int first_idx = -1;
        int prev_idx = -1;
        int min_dist = INT_MAX;
        int index = 1; // 0-based index for curr (node after head)

        while (curr->next != nullptr) {
            ListNode* nextNode = curr->next;
            
            // Check if curr is a local maxima or minima
            bool isMaxima = (curr->val > prev->val) && (curr->val > nextNode->val);
            bool isMinima = (curr->val < prev->val) && (curr->val < nextNode->val);

            if (isMaxima || isMinima) {
                if (first_idx == -1) {
                    first_idx = index;
                } else {
                    min_dist = min(min_dist, index - prev_idx);
                }
                prev_idx = index;
            }

            prev = curr;
            curr = nextNode;
            index++;
        }

        // Return [-1, -1] if fewer than 2 critical points were found
        if (first_idx == -1 || prev_idx == first_idx) {
            return {-1, -1};
        }

        return {min_dist, prev_idx - first_idx};
    }
};
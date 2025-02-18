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
        ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
            int carry = 0; // 记录进位情况
            ListNode *head = nullptr, *tail = nullptr;
    
            while (l1 || l2 || carry != 0) {
                int a = l1 ? l1->val : 0;
                int b = l2 ? l2->val : 0;
    
                int cur = a + b + carry;
                carry = cur / 10;
                cur %= 10;
    
                if (!head) {
                    head = tail = new ListNode(cur);
                } else {
                    tail->next = new ListNode(cur);
                    tail = tail->next;
                }
    
                if (l1)
                    l1 = l1->next;
                if (l2)
                    l2 = l2->next;
            }
            return head;
        }
    };
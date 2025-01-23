class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode* dummyhead = new ListNode(0);
        dummyhead->next = head;
        ListNode* cur = dummyhead;
        while (cur->next != nullptr && cur->next->next != nullptr) {
            ListNode* tmp = cur->next;
            ListNode* final = cur->next->next->next;

            cur->next = cur->next->next;
            cur->next->next = tmp;
            tmp->next = final;

            cur = cur->next->next;
        }
        return dummyhead->next; // 注意不能直接返回head
    }
};
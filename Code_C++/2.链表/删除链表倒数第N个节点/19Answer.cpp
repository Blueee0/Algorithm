class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummyhead = new ListNode(0);
        dummyhead->next = head;
        ListNode* fast = dummyhead;
        ListNode* slow = dummyhead;
        n++; // 移动n+1步
        while (n-- && fast != nullptr) {
            fast = fast->next;
        }
        while (
            fast !=
            nullptr) { // 当fast移动到null的时候，slow就到了要删除节点的前一个节点
            fast = fast->next;
            slow = slow->next;
        }
        ListNode* tmp = slow->next;
        slow->next = slow->next->next;
        delete tmp;
        tmp = nullptr;
        return dummyhead->next;
    }
};
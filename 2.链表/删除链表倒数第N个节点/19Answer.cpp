class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummyhead = new ListNode(0);
        dummyhead->next = head;
        ListNode* fast = dummyhead;
        ListNode* slow = dummyhead;
        n++; // �ƶ�n+1��
        while (n-- && fast != nullptr) {
            fast = fast->next;
        }
        while (
            fast !=
            nullptr) { // ��fast�ƶ���null��ʱ��slow�͵���Ҫɾ���ڵ��ǰһ���ڵ�
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
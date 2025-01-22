
// ԭ����ɾ��Ԫ��
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        // ɾ��ͷ���
        while (head != NULL && head->val == val) { // ע�����ﲻ��if
            ListNode* tmp = head;
            head = head->next;
            delete tmp;
        }

        // ɾ����ͷ���
        ListNode* cur = head;
        while (cur != NULL && cur->next!= NULL) {
            if (cur->next->val == val) {
                ListNode* tmp = cur->next;
                cur->next = cur->next->next;
                delete tmp;
            } else {
                cur = cur->next;
            }
        }
        return head;
    }
};

// ʹ������ͷ���
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode* dummyHead = new ListNode(0); // ����һ������ͷ���
        dummyHead->next = head; // ������ͷ���ָ��head���������������ɾ������
        ListNode* cur = dummyHead;
        while (cur->next != NULL) {
            if(cur->next->val == val) {
                ListNode* tmp = cur->next;
                cur->next = cur->next->next;
                delete tmp;
            } else {
                cur = cur->next;
            }
        }
        head = dummyHead->next; // ע�ⷵ��ͷָ��
        delete dummyHead;
        return head;
    }
};
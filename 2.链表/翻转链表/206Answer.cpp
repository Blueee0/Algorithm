// ˫ָ�뷨
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* cur = head;
        ListNode* pre = nullptr;
        ListNode* tmp = nullptr;
        while (cur != nullptr) {
            tmp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = tmp;
        }
        return pre;
    }
};

// �ݹ鷨
class Solution {
public:
    ListNode* reverse(ListNode* cur, ListNode* pre) {
        if (cur == nullptr) {
            return pre;
        }
        ListNode* tmp = cur->next;
        cur->next = pre;
        return reverse(tmp, cur);
    }

    ListNode* reverseList(ListNode* head) { 
        return reverse(head, nullptr); 
    }

};

// �Ӻ���ǰ��תָ��
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        // ��Ե�����ж�
        if(head == NULL) return NULL;
        if (head->next == NULL) return head;
        
        // �ݹ���ã���ת�ڶ����ڵ㿪ʼ���������
        ListNode *last = reverseList(head->next);
        // ��תͷ�ڵ���ڶ����ڵ��ָ��
        head->next->next = head;
        // ��ʱ�� head �ڵ�Ϊβ�ڵ㣬next ��Ҫָ�� NULL
        head->next = NULL;
        return last;
    }
}; 
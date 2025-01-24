class Solution {
public:
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
        ListNode* curA = headA;
        ListNode* curB = headB;

        // �����������ĳ��Ȳ�ǵð�curA��curBָ��ͷָ��
        int m = getLength(curA);
        int n = getLength(curB);
        curA = headA;
        curB = headB;

        // **��curAָ�������
        if (n > m) {
            swap(m, n);
            swap(curA, curB);
        }
        // ��curA��curB��ͬһ����ϣ�ĩβλ�ö��룩
        int gap = m - n;
        while (gap--) {
            curA = curA->next;
        }

        // ����curA �� curB��������ͬ��ֱ�ӷ���
        while (curA != NULL) {
            if (curA == curB) {
                return curA;
            }
            curA = curA->next;
            curB = curB->next;
        }
        return NULL;
    }

private:
    // ���������
    int getLength(ListNode* head) {
        int length = 0;
        while (head != NULL) {
            length++;
            head = head->next;
        }
        return length;
    }
};
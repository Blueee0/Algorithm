class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* preHead = new ListNode(-1); // ����ͷ�ڵ㣬��󷵻�preHead->next
        ListNode* prev = preHead;

        while (l1 != nullptr && l2 != nullptr) {
            if (l1->val < l2->val) {
                prev->next = l1;
                l1 = l1->next;
            } else {
                prev->next = l2;
                l2 = l2->next;
            }
            prev = prev->next;
        }

        // �ϲ��� l1 �� l2
        // ���ֻ��һ����δ���ϲ��꣬����ֱ�ӽ�����ĩβָ��δ�ϲ����������
        if(l1==nullptr){
            prev->next = l2;
        }else{
            prev->next = l1;
        }

        return preHead->next;
    }
};
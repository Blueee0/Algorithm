class Solution {
public:
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
        ListNode* curA = headA;
        ListNode* curB = headB;

        // 求出两个链表的长度差，记得把curA、curB指回头指针
        int m = getLength(curA);
        int n = getLength(curB);
        curA = headA;
        curB = headB;

        // **让curA指向最长链表
        if (n > m) {
            swap(m, n);
            swap(curA, curB);
        }
        // 让curA和curB在同一起点上（末尾位置对齐）
        int gap = m - n;
        while (gap--) {
            curA = curA->next;
        }

        // 遍历curA 和 curB，遇到相同则直接返回
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
    // 求出链表长度
    int getLength(ListNode* head) {
        int length = 0;
        while (head != NULL) {
            length++;
            head = head->next;
        }
        return length;
    }
};
// 双指针法
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

// 递归法
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

// 从后向前翻转指针
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        // 边缘条件判断
        if(head == NULL) return NULL;
        if (head->next == NULL) return head;
        
        // 递归调用，翻转第二个节点开始往后的链表
        ListNode *last = reverseList(head->next);
        // 翻转头节点与第二个节点的指向
        head->next->next = head;
        // 此时的 head 节点为尾节点，next 需要指向 NULL
        head->next = NULL;
        return last;
    }
}; 
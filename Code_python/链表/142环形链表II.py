class Solution:
    def detectCycle(self, head: Optional[ListNode]) -> Optional[ListNode]:
        slow = head
        fast = head

        while fast and fast.next:
            slow = slow.next
            fast = fast.next.next
            
            if slow == fast: # 说明此时有环
                slow = head
                while slow != fast:
                    slow = slow.next
                    fast = fast.next
                return slow
        return None
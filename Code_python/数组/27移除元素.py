class Solution:
    def removeElement(self, nums: List[int], val: int) -> int:
        slow = 0   # 慢指针指向下标
        fast = 0   # 快指针指向当前元素
        size = len(nums)
        while fast < size :
            if nums[fast] != val:
                nums[slow] = nums[fast]
                slow += 1
            fast += 1
        return slow
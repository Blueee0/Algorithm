class Solution:
    def sortedSquares(self, nums: List[int]) -> List[int]:
        left = 0
        right = len(nums) - 1
        i = len(nums) - 1
        res = [float('inf')] * len(nums) # 需要提前定义列表，存放结果
        while left <= right:
            if(nums[left] ** 2 < nums[right] **2):
                res[i] = nums[right] **2
                right -= 1
            else:
                res[i] = nums[left] **2
                left += 1
            i -= 1
        return res
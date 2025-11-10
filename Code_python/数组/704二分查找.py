class Solution(object):
    def search(self, nums, target):
        # 定义target在左闭右闭的区间里，[left, right]
        left = 0
        right = len(nums) - 1
        while left <= right:
            middle = (left + right) / 2
            if nums[middle] > target:
                right = middle - 1
            elif nums[middle] < target:
                left = middle + 1  # target在右区间，所以[middle + 1, right]
            else:
                return middle  # 数组中找到目标值，直接返回下标
        return -1  # 未找到目标值
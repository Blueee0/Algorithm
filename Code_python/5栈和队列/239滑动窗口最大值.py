from collections import deque
class Solution:
    def maxSlidingWindow(self, nums: List[int], k: int) -> List[int]:
        max_list = [] # 结果集合
        kept_nums = deque() # 单调队列

        for i in range(len(nums)):
            update_kept_nums(kept_nums, nums[i]) # 右侧新元素加入

            if i >= k and nums[i - k] == kept_nums[0]: # 左侧旧元素如果等于单调队列头元素，需要移除头元素
                kept_nums.popleft()

            if i >= k - 1:
                max_list.append(kept_nums[0])

        return max_list

def update_kept_nums(kept_nums, num): # num 是新加入的元素
    # 所有小于新元素的队列尾部元素，在新元素出现后，都是没有价值的，都需要被移除
    while kept_nums and num > kept_nums[-1]:
        kept_nums.pop()

    kept_nums.append(num)
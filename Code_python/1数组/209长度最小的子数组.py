class Solution:
    def minSubArrayLen(self, target: int, nums: List[int]) -> int:
        left = 0
        right = 0
        min_len = float('inf')
        cur_sum = 0 #当前的累加值
        while right < len(nums):
            cur_sum += nums[right]
            while(cur_sum >= target):
                min_len = min(min_len, right - left + 1)
                cur_sum -= nums[left]
                left += 1
            right += 1
        if min_len == float('inf') :
            return 0
        else:
            return min_len
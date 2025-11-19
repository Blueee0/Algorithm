class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        records = dict()

        # 遍历当前元素，并在map中寻找是否有匹配的key
        for index, value in enumerate(nums):  
            if target - value in records:   
                return [records[target - value], index]
            # 如果没找到匹配对，就把访问过的元素和下标加入到map中
            records[value] = index    
        return []
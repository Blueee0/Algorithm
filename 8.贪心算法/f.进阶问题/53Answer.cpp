class Solution {
    public:
        int maxSubArray(vector<int>& nums) {
            int result = INT32_MIN;
            int count = 0;
            for (int i = 0; i < nums.size(); i++) {
                count += nums[i];
                // 取区间累计的最大值
                if (count > result) { 
                    result = count;
                }
                // 如果连续和小于0，立刻重新开始
                if (count <= 0)
                    count = 0;
            }
            return result;
        }
    };
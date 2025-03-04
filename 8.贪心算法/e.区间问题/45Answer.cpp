class Solution {
    public:
        int jump(vector<int>& nums) {
            if (nums.size() == 1)
                return 0;
    
            int cur = 0, next = 0; // 记录当前和下一步的覆盖范围
            int result = 0;        // 记录步数
    
            for (int i = 0; i < nums.size(); i++) {
                next = max(next, i + nums[i]);
                if (i == cur) { // 遇到当前覆盖最远距离下标
                    result++;
                    cur = next;
                    // 当前覆盖最远距到达集合终点，不用做result++操作了，直接结束
                    if (cur >= nums.size() - 1)
                        break;
                }
            }
            return result;
        }
    };
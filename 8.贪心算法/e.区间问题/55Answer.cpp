class Solution {
    public:
        bool canJump(vector<int>& nums) {
            int cover = 0;
            if (nums.size() == 1)
                return true;
    
            // i 一定在覆盖范围内活动！
            for (int i = 0; i <= cover; i++) {
                // 只有cover变大了，才要更新cover
                cover = max(cover, i + nums[i]);
                if (cover >= nums.size() - 1)
                    return true;
            }
            
            return false;
        }
    };
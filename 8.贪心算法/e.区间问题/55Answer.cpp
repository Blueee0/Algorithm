class Solution {
    public:
        bool canJump(vector<int>& nums) {
            int cover = 0;
            if (nums.size() == 1)
                return true;
    
            // i һ���ڸ��Ƿ�Χ�ڻ��
            for (int i = 0; i <= cover; i++) {
                // ֻ��cover����ˣ���Ҫ����cover
                cover = max(cover, i + nums[i]);
                if (cover >= nums.size() - 1)
                    return true;
            }
            
            return false;
        }
    };
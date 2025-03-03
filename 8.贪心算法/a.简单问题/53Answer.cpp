class Solution {
    public:
        int maxSubArray(vector<int>& nums) {
            int result = INT32_MIN;
            int count = 0;
            for (int i = 0; i < nums.size(); i++) {
                count += nums[i];
                // ȡ�����ۼƵ����ֵ
                if (count > result) { 
                    result = count;
                }
                // ���������С��0���������¿�ʼ
                if (count <= 0)
                    count = 0;
            }
            return result;
        }
    };
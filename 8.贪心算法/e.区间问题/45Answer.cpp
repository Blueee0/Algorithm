class Solution {
    public:
        int jump(vector<int>& nums) {
            if (nums.size() == 1)
                return 0;
    
            int cur = 0, next = 0; // ��¼��ǰ����һ���ĸ��Ƿ�Χ
            int result = 0;        // ��¼����
    
            for (int i = 0; i < nums.size(); i++) {
                next = max(next, i + nums[i]);
                if (i == cur) { // ������ǰ������Զ�����±�
                    result++;
                    cur = next;
                    // ��ǰ������Զ�ൽ�Ｏ���յ㣬������result++�����ˣ�ֱ�ӽ���
                    if (cur >= nums.size() - 1)
                        break;
                }
            }
            return result;
        }
    };
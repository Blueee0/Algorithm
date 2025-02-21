class Solution {
    public:
        TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
            // ��ֹ����������Ҷ�ӽڵ㣨ע�⣬����û�п��ǿ�������������������index>0��
            if (nums.size() == 1) {
                return new TreeNode(nums[0]);
            }
    
            // �нڵ�
            int maxVal = 0; // ���ֵ����ڵ�
            int index = 0;  // �±�ָ�������
            for (int i = 0; i < nums.size(); i++) {
                if (nums[i] > maxVal) {
                    maxVal = nums[i];
                    index = i;
                }
            }
            TreeNode* node = new TreeNode(maxVal);
    
            // ��
            if (index > 0) {
                vector<int> Leftvec(nums.begin(), nums.begin() + index);
                node->left = constructMaximumBinaryTree(Leftvec);
            }
            // ��
            if (index < nums.size() - 1) {
                vector<int> Rightvec(nums.begin() + index + 1, nums.end());
                node->right = constructMaximumBinaryTree(Rightvec);
            }
            return node;
        }
    };
class Solution {
    public:
        TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
            // 终止条件：到达叶子节点（注意，这里没有考虑空数组的情况，所以下文index>0）
            if (nums.size() == 1) {
                return new TreeNode(nums[0]);
            }
    
            // 中节点
            int maxVal = 0; // 最大值构造节点
            int index = 0;  // 下标分割左右树
            for (int i = 0; i < nums.size(); i++) {
                if (nums[i] > maxVal) {
                    maxVal = nums[i];
                    index = i;
                }
            }
            TreeNode* node = new TreeNode(maxVal);
    
            // 左
            if (index > 0) {
                vector<int> Leftvec(nums.begin(), nums.begin() + index);
                node->left = constructMaximumBinaryTree(Leftvec);
            }
            // 右
            if (index < nums.size() - 1) {
                vector<int> Rightvec(nums.begin() + index + 1, nums.end());
                node->right = constructMaximumBinaryTree(Rightvec);
            }
            return node;
        }
    };
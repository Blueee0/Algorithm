class Solution {
    public:
        // 前序遍历：中左右
        TreeNode* insertIntoBST(TreeNode* root, int val) {
            if (root == nullptr) {
                // 找到了叶子节点，就是要插入的位置
                TreeNode* node = new TreeNode(val);
                return node; // 返回给上一层
            }
            if (val < root->val)
                root->left = insertIntoBST(root->left, val);
            if (val > root->val)
                root->right = insertIntoBST(root->right, val);
            return root;
        }
    };
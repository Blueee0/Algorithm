class Solution {
    public:
        TreeNode* pre = nullptr; // 全局变量
        bool isValidBST(TreeNode* root) {
            if (root == nullptr)
                return true;
            bool left = isValidBST(root->left); // 左
            if (pre != nullptr && pre->val >= root->val)
                return false;
            pre = root;
            bool right = isValidBST(root->right); // 右
            return left && right;
        }
    };
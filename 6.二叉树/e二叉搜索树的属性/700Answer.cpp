class Solution {
    public:
        TreeNode* searchBST(TreeNode* root, int val) {
            if (root == nullptr || root->val == val)
                return root;
            TreeNode* result = nullptr; // ¥Ê∑µªÿ÷µ
            if (val < root->val)
                result = searchBST(root->left, val);
            if (val > root->val)
                result = searchBST(root->right, val);
            return result;
        }
    };
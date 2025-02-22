class Solution {
    public:
        TreeNode* pre = nullptr; // ȫ�ֱ���
        bool isValidBST(TreeNode* root) {
            if (root == nullptr)
                return true;
            bool left = isValidBST(root->left); // ��
            if (pre != nullptr && pre->val >= root->val)
                return false;
            pre = root;
            bool right = isValidBST(root->right); // ��
            return left && right;
        }
    };
class Solution {
    public:
        TreeNode* trimBST(TreeNode* root, int low, int high) {
            if (root == nullptr)
                return nullptr;
            if (root->val < low) {
                TreeNode* right = trimBST(root->right, low, high);
                return right;
            }
            if (root->val > high) {
                TreeNode* right = trimBST(root->left, low, high);
                return right;
            }
            root->left = trimBST(root->left, low, high);
            root->right = trimBST(root->right, low, high);
            return root;
        }
    };
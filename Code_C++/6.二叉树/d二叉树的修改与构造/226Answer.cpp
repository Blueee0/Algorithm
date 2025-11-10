class Solution {
    public:
        TreeNode* invertTree(TreeNode* root) {
            if (root == nullptr)
                return root;
            swap(root->left, root->right); // ÷–
            invertTree(root->left);        // ◊Û
            invertTree(root->right);       // ”“
            return root;
        }
    };
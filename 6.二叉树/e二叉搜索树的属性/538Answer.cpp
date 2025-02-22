class Solution {
    public:
        TreeNode* pre = nullptr;
        void traversal(TreeNode* root) {
            // ����˳���ң��У���
            if (root == nullptr)
                return;
            traversal(root->right);
    
            if (pre != nullptr) {
                root->val += pre->val;
            }
            pre = root;
    
            traversal(root->left);
        }
    
        TreeNode* convertBST(TreeNode* root) {
            traversal(root);
            return root;
        }
    };
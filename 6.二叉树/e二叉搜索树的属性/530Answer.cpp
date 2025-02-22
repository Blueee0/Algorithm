class Solution {
    public:
        int result = INT_MAX;
        TreeNode* pre = nullptr;
        void traversal(TreeNode* cur) {
            if (cur == nullptr)
                return;
            traversal(cur->left);
            if (pre != nullptr) {
                result = min(result, cur->val - pre->val);
            }
            pre = cur;
            traversal(cur->right);
        }
    
        int getMinimumDifference(TreeNode* root) {
            traversal(root);
            return result;
        }
    };
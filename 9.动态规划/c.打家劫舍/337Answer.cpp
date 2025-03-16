class Solution {
    public:
        vector<int> traversal(TreeNode* cur) {
            if (cur == NULL)
                return vector<int>{0, 0};
            vector<int> left = traversal(cur->left);   // ×ó
            vector<int> right = traversal(cur->right); // ÓÒ
    
            // Íµcur
            int val1 = cur->val + left[0] + right[0];
            // ²»Íµcur
            int val2 = max(left[0], left[1]) + max(right[0], right[1]);
            return {val2, val1};
        }
    
        int rob(TreeNode* root) {
            vector<int> result = traversal(root);
            return max(result[0], result[1]);
        }
    };
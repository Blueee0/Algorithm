class Solution {
    public:
        // 前序遍历：中左右
        bool traversal(TreeNode* node, int targetSum) {
            if (node->left == nullptr && node->right == nullptr) {
                if (targetSum == 0) {
                    return true;
                } else {
                    return false;
                }
            }
            // 本层处理逻辑
            if (node->left) {
                targetSum -= node->left->val;
                if (traversal(node->left, targetSum))
                    return true; // 继续返回true！
                targetSum += node->left->val;
            }
    
            if (node->right) {
                targetSum -= node->right->val;
                if (traversal(node->right, targetSum))
                    return true; // 继续返回true！
                targetSum += node->right->val;
            }
            return false;
        }
    
        bool hasPathSum(TreeNode* root, int targetSum) {
            if (root == nullptr) {
                return false;
            }
            return traversal(root, targetSum - root->val);
        }
    };
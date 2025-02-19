class Solution {
    public:
        // ǰ�������������
        bool traversal(TreeNode* node, int targetSum) {
            if (node->left == nullptr && node->right == nullptr) {
                if (targetSum == 0) {
                    return true;
                } else {
                    return false;
                }
            }
            // ���㴦���߼�
            if (node->left) {
                targetSum -= node->left->val;
                if (traversal(node->left, targetSum))
                    return true; // ��������true��
                targetSum += node->left->val;
            }
    
            if (node->right) {
                targetSum -= node->right->val;
                if (traversal(node->right, targetSum))
                    return true; // ��������true��
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
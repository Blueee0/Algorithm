class Solution {
    public:
        // 后序遍历：左右中
        int sumOfLeftLeaves(TreeNode* root) {
            // 空节点时返回
            if (root == nullptr)
                return 0;
            // 处理到叶子结点时，返回
            if (root->left == nullptr && root->right == nullptr)
                return 0;
    
            // 注意：如果直接return，会直接返回了左子节点的值，并没有真的递归
            int sum = 0;
            if (root->left != nullptr && root->left->left == nullptr &&
                root->left->right == nullptr) {
                sum += root->left->val;
            }
            sum += sumOfLeftLeaves(root->left);
            sum += sumOfLeftLeaves(root->right);
            return sum;
        }
    };
class Solution {
    public:
        // 返回值，传入参数
        bool compare(TreeNode* left, TreeNode* right) {
            // 终止条件，四种情况
            if (left == nullptr && right != nullptr) {
                return false;
            } else if (left != nullptr && right == nullptr) {
                return false;
            } else if (left == nullptr && right == nullptr) {
                return true;
            } else if (left->val != right->val) {
                return false;
            }
            // 当前递归的返回逻辑
            bool outside = compare(left->left, right->right);
            bool inside = compare(left->right, right->left);
            bool isSame = outside && inside;
            return isSame;
        }
        bool isSymmetric(TreeNode* root) {
            if (root == nullptr)
                return true;
            return compare(root->left, root->right);
        }
    };
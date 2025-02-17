class Solution {
    public:
        // ����ֵ���������
        bool compare(TreeNode* left, TreeNode* right) {
            // ��ֹ�������������
            if (left == nullptr && right != nullptr) {
                return false;
            } else if (left != nullptr && right == nullptr) {
                return false;
            } else if (left == nullptr && right == nullptr) {
                return true;
            } else if (left->val != right->val) {
                return false;
            }
            // ��ǰ�ݹ�ķ����߼�
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
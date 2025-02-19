class Solution {
    public:
        // ���������������
        int sumOfLeftLeaves(TreeNode* root) {
            // �սڵ�ʱ����
            if (root == nullptr)
                return 0;
            // ����Ҷ�ӽ��ʱ������
            if (root->left == nullptr && root->right == nullptr)
                return 0;
    
            // ע�⣺���ֱ��return����ֱ�ӷ��������ӽڵ��ֵ����û����ĵݹ�
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
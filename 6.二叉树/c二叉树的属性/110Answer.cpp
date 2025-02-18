class Solution {
    public:
        int getHeight(TreeNode* node) {
    
            if (node == NULL) {
                return 0;
            }
    
            int leftHeight = getHeight(node->left); // ��
            if (leftHeight == -1)
                return -1;
            int rightHeight = getHeight(node->right); // ��
            if (rightHeight == -1)
                return -1;
    
            int result;
            if (abs(leftHeight - rightHeight) > 1) {
                result = -1; // �ж��Ƿ�Ϊƽ�������
            } else {         // �Ե�ǰ�ڵ�Ϊ���ڵ���������߶�
                result = 1 + max(leftHeight, rightHeight);
            }
    
            return result;
        }
        bool isBalanced(TreeNode* root) {
            return getHeight(root) == -1 ? false : true;
        }
    };
class Solution {
    public:
        int getHeight(TreeNode* node) {
    
            if (node == NULL) {
                return 0;
            }
    
            int leftHeight = getHeight(node->left); // 左
            if (leftHeight == -1)
                return -1;
            int rightHeight = getHeight(node->right); // 右
            if (rightHeight == -1)
                return -1;
    
            int result;
            if (abs(leftHeight - rightHeight) > 1) {
                result = -1; // 判断是否为平衡二叉树
            } else {         // 以当前节点为根节点的树的最大高度
                result = 1 + max(leftHeight, rightHeight);
            }
    
            return result;
        }
        bool isBalanced(TreeNode* root) {
            return getHeight(root) == -1 ? false : true;
        }
    };
class Solution {
    public:
        int getHeight(TreeNode* node) {
            if (node == nullptr)
                return 0;
            int leftHeight = getHeight(node->left);        // ◊Û
            int rightHeight = getHeight(node->right);      // ”“
            int height = 1 + max(leftHeight, rightHeight); // ÷–
            return height;
        }
    
        int maxDepth(TreeNode* root) { 
            return getHeight(root); 
        }
    };
class Solution {
    public:
        // 后序遍历：左右中
        TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
            if (root == NULL)
                return NULL;
    
            if (root == p || root == q)
                return root;
    
            TreeNode* left =
                lowestCommonAncestor(root->left, p, q); // 左子树是否出现了p 或 q
            TreeNode* right =
                lowestCommonAncestor(root->right, p, q); // 右子树是否出现了p 或 q
            if (left != NULL && right != NULL)
                return root;    // 左有，右有，则当前节点为公共祖先
            if (left == NULL && right != NULL)
                return right;   // 已经找到了公共祖先，就继续返回到root
            else if (left != NULL && right == NULL)
                return left;    // 已经找到了公共祖先，就继续返回到root
            else
                return NULL;
        }
    };
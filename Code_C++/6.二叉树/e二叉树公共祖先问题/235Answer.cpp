class Solution {
    public:
        // Ç°Ðò±éÀú£ºÖÐ×óÓÒ
        TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
            if (root == NULL)
                return NULL;
    
            if (root->val > p->val && root->val < q->val) {
                return root;
            }
    
            if (root->val > p->val && root->val > q->val) {
                return lowestCommonAncestor(root->left, p, q);
            }
            if (root->val < p->val && root->val < q->val) {
                return lowestCommonAncestor(root->right, p, q);
            }
            return root;
        }
    };
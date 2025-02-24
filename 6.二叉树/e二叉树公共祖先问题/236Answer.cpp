class Solution {
    public:
        // ���������������
        TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
            if (root == NULL)
                return NULL;
    
            if (root == p || root == q)
                return root;
    
            TreeNode* left =
                lowestCommonAncestor(root->left, p, q); // �������Ƿ������p �� q
            TreeNode* right =
                lowestCommonAncestor(root->right, p, q); // �������Ƿ������p �� q
            if (left != NULL && right != NULL)
                return root;    // ���У����У���ǰ�ڵ�Ϊ��������
            if (left == NULL && right != NULL)
                return right;   // �Ѿ��ҵ��˹������ȣ��ͼ������ص�root
            else if (left != NULL && right == NULL)
                return left;    // �Ѿ��ҵ��˹������ȣ��ͼ������ص�root
            else
                return NULL;
        }
    };
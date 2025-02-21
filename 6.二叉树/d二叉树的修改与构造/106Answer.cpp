class Solution {
    public:
        TreeNode* traversal(vector<int>& inorder, vector<int>& postorder) {
            // ��ֹ����������Ϊ0 -> �м�ڵ�Ϊ��
            if (postorder.size() == 0)
                return nullptr;
    
            // ���㣺��¼�м�ڵ��ֵ����ǰ�ĸ��ڵ㣩
            int value = postorder[postorder.size() - 1];
            TreeNode* root = new TreeNode(value);
            if (postorder.size() == 1) // ������Ҷ�ӽڵ㣬��ֹ
                return root;
    
            // �ݹ��߼������������顢�к�������
            // ���������飨������������
            int index = 0;
            for (index = 0; index < inorder.size(); index++) {
                if (inorder[index] == value)
                    break;
            }
            vector<int> leftInorder(inorder.begin(), inorder.begin() + index);
            vector<int> rightInorder(inorder.begin() + index + 1, inorder.end());
    
            // �ݹ��߼����к�������
            // postorder ����ĩβԪ�أ���Ϊ���Ԫ�ؾ����м�ڵ㣬�Ѿ��ù���
            postorder.resize(postorder.size() - 1);
            vector<int> leftPostorder(postorder.begin(), postorder.begin() + leftInorder.size());
            vector<int> rightPostorder(postorder.begin() + leftInorder.size(), postorder.end());
            
            // �ݹ�
            root->left = traversal(leftInorder,leftPostorder);
            root->right = traversal(rightInorder,rightPostorder);
    
            return root;
        }
        TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
            if (inorder.size() == 0 || postorder.size() == 0) 
                return NULL;
            return traversal(inorder, postorder);
        }
    };
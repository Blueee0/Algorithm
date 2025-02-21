/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */
class Solution {
    public:
        TreeNode* traversal(vector<int>& preorder, vector<int>& inorder) {
            // ��ֹ������ǰ�����Ϊ��
            if (preorder.size() == 0)
                return nullptr;
    
            int val = preorder[0];
            TreeNode* root = new TreeNode(val);
            if (preorder.size() == 1)
                return root;
    
            int index = 0;
            for (index = 0; index < preorder.size(); index++) {
                if (inorder[index] == val)
                    break;
            }
    
            // ������������
            vector<int> leftInorder(inorder.begin(), inorder.begin() + index);
            vector<int> rightInorder(inorder.begin() + index + 1, inorder.end());
    
            // ��ǰ�������ҡ�ע�⣡��ǰ�����ǰ��Ӧ��������������
            vector<int> leftPreorder(preorder.begin() + 1,
                                     preorder.begin() + leftInorder.size() + 1);
            vector<int> rightPreorder(preorder.begin() + leftInorder.size() + 1,
                                      preorder.end());
    
            root->left = traversal(leftPreorder, leftInorder);
            root->right = traversal(rightPreorder, rightInorder);
            return root;
        }
    
        TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
            if (preorder.size() == 0 || inorder.size() == 0)
                return nullptr;
            return traversal(preorder, inorder);
        }
    };
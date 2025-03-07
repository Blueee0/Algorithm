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
        int result = 0;
    
        // 0���ýڵ��޸��ǡ�1�����ڵ�������ͷ��2�����ڵ��и���
        int traversal(TreeNode* cur) {
            // �սڵ㣬�ýڵ��и���
            if (cur == nullptr)
                return 2;
    
            int left = traversal(cur->left);
            int right = traversal(cur->right);
    
            // ���Һ��Ӷ��и���
            if (left == 2 && right == 2)
                return 0;
            // ���Һ���������һ���޸���
            if (left == 0 || right == 0) {
                result++;
                return 1;
            }
            // ���Һ���������һ��������ͷ
            if (left == 1 || right == 1)
                return 2;
            return -1;
        }
    
        int minCameraCover(TreeNode* root) {
            
            // root �޸���
            if (traversal(root) == 0) {
                result++;
            }
    
            return result;
        }
    };
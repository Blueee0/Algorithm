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
        void traversal(TreeNode* node, vector<int>& path, vector<string>& result) {
    
            path.push_back(node->val); // �У�Ϊ�˰�Ҷ�ӽڵ��ֵ����path
    
            // ������Ҷ�ӽ��ʱ�����ؽ��
            if (node->left == nullptr && node->right == nullptr) {
                // result.push_back(path)����path���¼��·��תΪstring��ʽ
                string sPath;
                for (int i = 0; i < path.size() - 1; i++) {
                    sPath += to_string(path[i]);
                    sPath += "->";
                }
                sPath += to_string(path[path.size() - 1]); // ��¼���һ���ڵ㣨Ҷ�ӽڵ㣩
                result.push_back(sPath);    // �ռ�һ��·��
                return;
            }
            // ���㴦���߼���ǰ������������ң�
            if (node->left) {
                traversal(node->left, path, result);
                path.pop_back(); // ����
            }
            if (node->right) {
                traversal(node->right, path, result);
                path.pop_back(); // ����
            }
        }
        
        vector<string> binaryTreePaths(TreeNode* root) {
            vector<string> result;
            vector<int> path;
            if (root == NULL)
                return result;
            traversal(root, path, result);
            return result;
        }
    };
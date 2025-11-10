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
    
            path.push_back(node->val); // 中：为了把叶子节点的值放入path
    
            // 当遇到叶子结点时，返回结果
            if (node->left == nullptr && node->right == nullptr) {
                // result.push_back(path)，将path里记录的路径转为string格式
                string sPath;
                for (int i = 0; i < path.size() - 1; i++) {
                    sPath += to_string(path[i]);
                    sPath += "->";
                }
                sPath += to_string(path[path.size() - 1]); // 记录最后一个节点（叶子节点）
                result.push_back(sPath);    // 收集一个路径
                return;
            }
            // 单层处理逻辑：前序遍历（中左右）
            if (node->left) {
                traversal(node->left, path, result);
                path.pop_back(); // 回溯
            }
            if (node->right) {
                traversal(node->right, path, result);
                path.pop_back(); // 回溯
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
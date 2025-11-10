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
        vector<vector<int>> levelOrder(TreeNode* root) {
            queue<TreeNode*> que;
            vector<vector<int>> result; // 二维数组
            if (root != NULL)
                que.push(root);
    
            while (!que.empty()) {
                int size = que.size();
                vector<int> vec;
                // 这里一定要使用固定大小size，不要使用que.size()，因为que.size是不断变化的
                for (int i = 0; i < size; i++) {
                    TreeNode* node = que.front();
                    que.pop();
                    vec.push_back(node->val);
                    if (node->left)
                        que.push(node->left);
                    if (node->right)
                        que.push(node->right);
                }
                result.push_back(vec); // 把一层的结果放进result当中
            }
            return result;
        }
    };
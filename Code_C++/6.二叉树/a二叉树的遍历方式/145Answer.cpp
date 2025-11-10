/*
struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
}
*/
// 递归方式
class Solution {
    public:
        void traversal(TreeNode* cur, vector<int>& vec) {
            if (cur == nullptr)
                return;
            traversal(cur->left, vec);
            traversal(cur->right, vec);
            vec.push_back(cur->val);
        }
    
        vector<int> postorderTraversal(TreeNode* root) {
            vector<int> result;
            traversal(root, result);
            return result;
        }
    };
// 非递归遍历
class Solution {
    public:
        vector<int> postorderTraversal(TreeNode* root) {
            stack<TreeNode*> st;
            vector<int> result;
    
            // 处理空树
            if (root == NULL)
                return result;
    
            // 从根节点开始处理
            st.push(root);
            while (!st.empty()) {
                TreeNode* node = st.top(); // 中
                st.pop();
                result.push_back(node->val);
                if (node->left)
                    st.push(node->left); // 左（空节点不入栈）
                if (node->right)
                    st.push(node->right); // 右（空节点不入栈）
            }
            reverse(result.begin(), result.end());
            return result;
        }
    };
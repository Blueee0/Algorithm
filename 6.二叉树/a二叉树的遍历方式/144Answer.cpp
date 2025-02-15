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
        // 1. 确定递归函数的参数和返回值
        void traversal(TreeNode* cur, vector<int>& vec) {
            // 2. 确定终止条件
            if (cur == nullptr)
                return;
            // 3. 确定单层递归的逻辑：中左右
            vec.push_back(cur->val);
            traversal(cur->left, vec);
            traversal(cur->right, vec);
        }
    
        vector<int> preorderTraversal(TreeNode* root) {
            vector<int> result;
            traversal(root, result);
            return result;
        }
    };

// 非递归遍历
class Solution {
    public:
        vector<int> preorderTraversal(TreeNode* root) {
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
                if (node != nullptr)
                    result.push_back(node->val);
                else
                    continue;
                if (node->right)
                    st.push(node->right); // 右（空节点不入栈）
                if (node->left)
                    st.push(node->left); // 左（空节点不入栈）
            }
            return result;
        }
    };
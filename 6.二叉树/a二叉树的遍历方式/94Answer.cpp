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
            vec.push_back(cur->val);
            traversal(cur->right, vec);
        }
    
        vector<int> inorderTraversal(TreeNode* root) {
            vector<int> result;
            traversal(root, result);
            return result;
        }
    };
// 非递归遍历
class Solution {
    public:
        vector<int> inorderTraversal(TreeNode* root) {
            vector<int> result;
            stack<TreeNode*> st;
            TreeNode* cur = root;
            while (cur != NULL || !st.empty()) {
                if (cur != NULL) {      // 指针来访问节点，访问到最底层
                    st.push(cur);       // 将访问的节点放进栈
                    cur = cur->left;                // 左
                } else {
                    cur = st.top();     // 从栈里弹出的数据，就是要处理的数据（放进result数组里的数据）
                    st.pop();
                    result.push_back(cur->val);     // 中
                    cur = cur->right;               // 右
                }
            }
            return result;
        }
    };
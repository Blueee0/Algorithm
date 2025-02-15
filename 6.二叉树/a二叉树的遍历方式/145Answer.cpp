/*
struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
}
*/
// �ݹ鷽ʽ
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
// �ǵݹ����
class Solution {
    public:
        vector<int> postorderTraversal(TreeNode* root) {
            stack<TreeNode*> st;
            vector<int> result;
    
            // �������
            if (root == NULL)
                return result;
    
            // �Ӹ��ڵ㿪ʼ����
            st.push(root);
            while (!st.empty()) {
                TreeNode* node = st.top(); // ��
                st.pop();
                result.push_back(node->val);
                if (node->left)
                    st.push(node->left); // �󣨿սڵ㲻��ջ��
                if (node->right)
                    st.push(node->right); // �ң��սڵ㲻��ջ��
            }
            reverse(result.begin(), result.end());
            return result;
        }
    };
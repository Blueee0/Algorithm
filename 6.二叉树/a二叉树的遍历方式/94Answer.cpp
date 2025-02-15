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
            vec.push_back(cur->val);
            traversal(cur->right, vec);
        }
    
        vector<int> inorderTraversal(TreeNode* root) {
            vector<int> result;
            traversal(root, result);
            return result;
        }
    };
// �ǵݹ����
class Solution {
    public:
        vector<int> inorderTraversal(TreeNode* root) {
            vector<int> result;
            stack<TreeNode*> st;
            TreeNode* cur = root;
            while (cur != NULL || !st.empty()) {
                if (cur != NULL) {      // ָ�������ʽڵ㣬���ʵ���ײ�
                    st.push(cur);       // �����ʵĽڵ�Ž�ջ
                    cur = cur->left;                // ��
                } else {
                    cur = st.top();     // ��ջ�ﵯ�������ݣ�����Ҫ��������ݣ��Ž�result����������ݣ�
                    st.pop();
                    result.push_back(cur->val);     // ��
                    cur = cur->right;               // ��
                }
            }
            return result;
        }
    };
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
        // 1. ȷ���ݹ麯���Ĳ����ͷ���ֵ
        void traversal(TreeNode* cur, vector<int>& vec) {
            // 2. ȷ����ֹ����
            if (cur == nullptr)
                return;
            // 3. ȷ������ݹ���߼���������
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

// �ǵݹ����
class Solution {
    public:
        vector<int> preorderTraversal(TreeNode* root) {
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
                if (node != nullptr)
                    result.push_back(node->val);
                else
                    continue;
                if (node->right)
                    st.push(node->right); // �ң��սڵ㲻��ջ��
                if (node->left)
                    st.push(node->left); // �󣨿սڵ㲻��ջ��
            }
            return result;
        }
    };
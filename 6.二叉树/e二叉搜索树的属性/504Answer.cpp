class Solution {
    public:
        TreeNode* pre = nullptr;
        int cnt = 0, maxCNT = 0;
        vector<int> result;
    
        void traversal(TreeNode* cur) {
            if (cur == nullptr)
                return;
    
            traversal(cur->left);
    
            if (pre == nullptr)
                cnt = 1; // ָ���һ���ڵ�
            else if (pre->val == cur->val)
                cnt++; // ֵ��ȣ����ִ���+1
            else
                cnt = 1; // �л�����һ����
            pre = cur;
            if (cnt == maxCNT) {
                result.push_back(cur->val);
            }
            if (cnt > maxCNT) {
                maxCNT = cnt;
                result.clear();
                result.push_back(cur->val);
            }
    
            traversal(cur->right);
        }
    
        vector<int> findMode(TreeNode* root) {
            traversal(root);
            return result;
        }
    };
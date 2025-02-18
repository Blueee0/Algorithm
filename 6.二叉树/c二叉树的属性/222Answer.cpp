// �ⷨһ��ʹ����ͨ�������ı�����ʽ����������������У�
class Solution {
    public:
        // 
        int getNum(TreeNode* node) {
            if (node == nullptr)
                return 0;
            int leftNum = getNum(node->left);
            int rightNum = getNum(node->right);
            return leftNum + rightNum + 1;
        }
        int countNodes(TreeNode* root) { 
            return getNum(root); 
        }
    };

// �ⷨ������ȫ�����������ж������Ƿ�����������(������Ⱥ��������һ��)��Ȼ�����ڵ��������ظ����ڵ�
class Solution {
    public:
        int getNum(TreeNode* node) {
            // ������
            if (node == nullptr)
                return 0;
    
            // �������������
            TreeNode* left = node->left;
            TreeNode* right = node->right;
            int leftdepth = 0, rightdepth = 0;
            while (left) {
                left = left->left;
                leftdepth++;
            }
            while (right) {
                right = right->right;
                rightdepth++;
            }
            if (leftdepth == rightdepth) {
                return (2 << leftdepth) - 1;
            }
    
            // ����ݹ��߼�
            int leftnum = getNum(node->left);
            int rightnum = getNum(node->right);
            return leftnum + rightnum + 1;
        }
        int countNodes(TreeNode* root) { 
            return getNum(root); 
        }
    };
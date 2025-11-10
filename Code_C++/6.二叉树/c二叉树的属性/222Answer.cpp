// 解法一：使用普通二叉树的遍历方式：后序遍历（左右中）
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

// 解法二：完全二叉树：先判断子树是否是满二叉树(向左深度和向右深度一致)，然后计算节点数量返回给父节点
class Solution {
    public:
        int getNum(TreeNode* node) {
            // 空子树
            if (node == nullptr)
                return 0;
    
            // 满二叉树的情况
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
    
            // 单层递归逻辑
            int leftnum = getNum(node->left);
            int rightnum = getNum(node->right);
            return leftnum + rightnum + 1;
        }
        int countNodes(TreeNode* root) { 
            return getNum(root); 
        }
    };
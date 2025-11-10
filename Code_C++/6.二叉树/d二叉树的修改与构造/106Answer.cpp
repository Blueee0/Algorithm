class Solution {
    public:
        TreeNode* traversal(vector<int>& inorder, vector<int>& postorder) {
            // 终止条件：后序为0 -> 中间节点为空
            if (postorder.size() == 0)
                return nullptr;
    
            // 本层：记录中间节点的值（当前的根节点）
            int value = postorder[postorder.size() - 1];
            TreeNode* root = new TreeNode(value);
            if (postorder.size() == 1) // 遍历到叶子节点，终止
                return root;
    
            // 递归逻辑：切中序数组、切后序数组
            // 切中序数组（左中序、右中序）
            int index = 0;
            for (index = 0; index < inorder.size(); index++) {
                if (inorder[index] == value)
                    break;
            }
            vector<int> leftInorder(inorder.begin(), inorder.begin() + index);
            vector<int> rightInorder(inorder.begin() + index + 1, inorder.end());
    
            // 递归逻辑：切后序数组
            // postorder 舍弃末尾元素，因为这个元素就是中间节点，已经用过了
            postorder.resize(postorder.size() - 1);
            vector<int> leftPostorder(postorder.begin(), postorder.begin() + leftInorder.size());
            vector<int> rightPostorder(postorder.begin() + leftInorder.size(), postorder.end());
            
            // 递归
            root->left = traversal(leftInorder,leftPostorder);
            root->right = traversal(rightInorder,rightPostorder);
    
            return root;
        }
        TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
            if (inorder.size() == 0 || postorder.size() == 0) 
                return NULL;
            return traversal(inorder, postorder);
        }
    };
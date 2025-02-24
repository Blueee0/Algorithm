class Solution {
    public:
        TreeNode* deleteNode(TreeNode* root, int key) {
            // 终止条件
            if (root == nullptr)
                return nullptr; // 没有找到删除节点
            if (root->val == key) {
                // 左子树为空，右子树为空
                if (root->left == nullptr && root->right == nullptr) {
                    delete root;
                    return nullptr;
                }
                // 左子树不为空，右子树为空
                else if (root->left != nullptr && root->right == nullptr) {
                    TreeNode* node = root->left;
                    delete root;
                    return node;
                }
                // 左子树为空，右子树不为空
                else if (root->left == nullptr && root->right != nullptr) {
                    TreeNode* node = root->right;
                    delete root;
                    return node;
                }
                // 左子树不为空，右子树不为空，将左子树放到右子树最左侧
                else {
                    TreeNode* rightSubtree = root->right;
                    while (rightSubtree->left != nullptr)
                        rightSubtree = rightSubtree->left;
                    rightSubtree->left = root->left;
                    TreeNode* node = root->right;
                    delete root;
                    return node;
                }
            }
            if (key < root->val)
                root->left = deleteNode(root->left, key);
            if (key > root->val)
                root->right = deleteNode(root->right, key);
            return root;
        }
    };
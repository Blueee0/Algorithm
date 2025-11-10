// ≤„–Ú±È¿˙
class Solution
{
public:
    int findBottomLeftValue(TreeNode *root)
    {
        queue<TreeNode *> que;
        int result;

        if (root != nullptr)
            que.push(root);

        while (!que.empty())
        {
            int size = que.size();
            vector<int> vec;

            for (int i = 0; i < size; i++)
            {
                TreeNode *node = que.front();
                que.pop();
                vec.push_back(node->val);
                if (node->left)
                    que.push(node->left);
                if (node->right)
                    que.push(node->right);
            }
            result = vec[0];
        }
        return result;
    }
};

// µ›πÈ±È¿˙
// µ›πÈ±È¿˙
class Solution {
    public:
        int maxDepth = 0;
        int result;
        void traversal(TreeNode* root, int depth) {
            if (root->left == nullptr && root->right == nullptr) {
                if (depth > maxDepth) {
                    maxDepth = depth;
                    result = root->val;
                }
            }
            if (root->left) {
                depth++;
                traversal(root->left, depth);
                depth--; // ªÿÀ›
            }
            if (root->right) {
                depth++;
                traversal(root->right, depth);
                depth--; // ªÿÀ›
            }
        }
        int findBottomLeftValue(TreeNode* root) {
            traversal(root, 0);
            return result;
        }
    };
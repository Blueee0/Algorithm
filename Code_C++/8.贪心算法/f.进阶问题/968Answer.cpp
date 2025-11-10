/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */
class Solution {
    public:
        int result = 0;
    
        // 0：该节点无覆盖、1：本节点有摄像头、2：本节点有覆盖
        int traversal(TreeNode* cur) {
            // 空节点，该节点有覆盖
            if (cur == nullptr)
                return 2;
    
            int left = traversal(cur->left);
            int right = traversal(cur->right);
    
            // 左右孩子都有覆盖
            if (left == 2 && right == 2)
                return 0;
            // 左右孩子至少有一个无覆盖
            if (left == 0 || right == 0) {
                result++;
                return 1;
            }
            // 左右孩子至少有一个有摄像头
            if (left == 1 || right == 1)
                return 2;
            return -1;
        }
    
        int minCameraCover(TreeNode* root) {
            
            // root 无覆盖
            if (traversal(root) == 0) {
                result++;
            }
    
            return result;
        }
    };
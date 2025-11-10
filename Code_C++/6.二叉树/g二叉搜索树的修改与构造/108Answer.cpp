class Solution {
    public:
        // 区间：左闭右闭
        TreeNode* traversal(vector<int>& nums, int left, int right) {
            // 终止条件
            if (left > right)
                return nullptr;
    
            // 数组中间的元素作为中间节点，然后构造左子树、右子树
            int mid = (left + right) / 2;
            TreeNode* root = new TreeNode(nums[mid]);
            root->left = traversal(nums, left, mid - 1);
            root->right = traversal(nums, mid + 1, right);
            return root;
        }
    
        TreeNode* sortedArrayToBST(vector<int>& nums) {
            TreeNode* root = traversal(nums, 0, nums.size() - 1);
            return root;
        }
    };
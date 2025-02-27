class Solution {
    public:
        vector<vector<int>> result;
        vector<int> path;
    
        void backtracking(vector<int>& nums, int startIndex) {
            result.push_back(path); // 每一次递归都要收获结果：子集
    
            // 终止条件可以不加
            if (startIndex == nums.size()) {
                return;
            }
    
            for (int i = startIndex; i < nums.size(); i++) {
                path.push_back(nums[i]);
                backtracking(nums, i + 1);
                path.pop_back();
            }
            return;
        }
        vector<vector<int>> subsets(vector<int>& nums) {
            result.clear();
            path.clear();
            backtracking(nums, 0);
            return result;
        }
    };
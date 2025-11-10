class Solution {
    public:
        vector<vector<int>> result;
        vector<int> path;
        void backtracking(vector<int>& nums, int startIndex) {
            result.push_back(path); // 每一次递归都要收获结果：子集
    
            for (int i = startIndex; i < nums.size(); i++) {
                if (i > startIndex && nums[i] == nums[i - 1]) {
                    continue;
                } else {
                    path.push_back(nums[i]);
                    backtracking(nums, i + 1);
                    path.pop_back();
                }
            }
            return;
        }
    
        vector<vector<int>> subsetsWithDup(vector<int>& nums) {
            result.clear();
            path.clear();
            sort(nums.begin(), nums.end());
            backtracking(nums, 0);
            return result;
        }
    };
    
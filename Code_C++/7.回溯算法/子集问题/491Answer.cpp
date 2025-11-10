class Solution {
    public:
        vector<vector<int>> result;
        vector<int> path;
    
        void backtracking(vector<int>& nums, int startIndex) {
            if (path.size() >= 2) {
                result.push_back(path);
                // 注意！这里不要加return，要取树上的节点
            }
            unordered_set<int> uset; // 使用set对本层元素进行去重
            for (int i = startIndex; i < nums.size(); i++) {
                if ((!path.empty() && nums[i] < path.back()) || uset.find(nums[i]) != uset.end()) {
                    // 当path不为空时，若读取元素小于path结尾（不构成非递减），则不需要进入递归
                    // 若发现当前取的数在本树层已经被用过，不进入递归
                    continue;
                }
                uset.insert(nums[i]); // 记录元素被使用过
                path.push_back(nums[i]);
                backtracking(nums, i + 1);
                path.pop_back();
            }
            return;
        }
    
        vector<vector<int>> findSubsequences(vector<int>& nums) {
            result.clear();
            path.clear();
            backtracking(nums, 0);
            return result;
        }
    };
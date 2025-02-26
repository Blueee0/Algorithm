class Solution {
    public:
        vector<vector<int>> result;
        vector<int> path;
    
        void backtracking(const vector<int>& candidates, int targetSum, int sum,
                          int startIndex) {
            // 终止条件：sum > targetSum 返回; sum == targetSum 收获
            if (sum > targetSum) {
                return;
            }
            if (sum == targetSum) {
                result.push_back(path);
                return;
            }
    
            for (int i = startIndex; i < candidates.size() && sum + candidates[i] <= targetSum; i++) {
                sum += candidates[i];
                path.push_back(candidates[i]);
                backtracking(candidates, targetSum, sum, i); // 注意：这里应该传入i，所以才能重复取当前元素
                sum -= candidates[i];
                path.pop_back();
            }
        }
    
        vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
            result.clear();
            path.clear();
            sort(candidates.begin(), candidates.end());
            backtracking(candidates, target, 0, 0);
            return result;
        }
    };
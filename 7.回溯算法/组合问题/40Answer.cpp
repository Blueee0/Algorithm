class Solution {
    public:
        vector<int> path;
        vector<vector<int>> result;
    
        void backtracking(const vector<int>& candidates, int targetSum, int sum,
                          int startIndex) {
            // sum == targetSum 收获结果
            if (sum == targetSum) {
                result.push_back(path);
                return;
            }
    
            for (int i = startIndex;i < candidates.size() && sum + candidates[i] <= targetSum; i++) {
                // 去重逻辑：i>startIndex 表明在同一树层第二个元素开始，然后如果树层重复，就不需要进入递归
                if (i > startIndex && candidates[i] == candidates[i - 1]) {
                    continue;
                }
                sum += candidates[i];
                path.push_back(candidates[i]);
                backtracking(candidates, targetSum, sum, i + 1);
                sum -= candidates[i];
                path.pop_back();
            }
        }
    
        vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
            sort(candidates.begin(), candidates.end());
            backtracking(candidates, target, 0, 0);
            return result;
        }
    };
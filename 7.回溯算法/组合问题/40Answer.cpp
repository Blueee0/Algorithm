class Solution {
    public:
        vector<int> path;
        vector<vector<int>> result;
    
        void backtracking(const vector<int>& candidates, int targetSum, int sum,
                          int startIndex) {
            // sum == targetSum �ջ���
            if (sum == targetSum) {
                result.push_back(path);
                return;
            }
    
            for (int i = startIndex;i < candidates.size() && sum + candidates[i] <= targetSum; i++) {
                // ȥ���߼���i>startIndex ������ͬһ����ڶ���Ԫ�ؿ�ʼ��Ȼ����������ظ����Ͳ���Ҫ����ݹ�
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
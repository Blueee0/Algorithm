class Solution {
    public:
        vector<vector<int>> result;
        vector<int> path;
    
        void backtracking(const vector<int>& candidates, int targetSum, int sum,
                          int startIndex) {
            // ��ֹ������sum > targetSum ����; sum == targetSum �ջ�
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
                backtracking(candidates, targetSum, sum, i); // ע�⣺����Ӧ�ô���i�����Բ����ظ�ȡ��ǰԪ��
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
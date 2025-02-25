class Solution {
    public:
        vector<int> path;
        vector<vector<int>> result;
    
        void backtracking(int k, int targetSum, int startIndex, int sum) {
            // ¼ôÖ¦
            if (sum > targetSum) {
                return;
            }
            // ÖÕÖ¹Ìõ¼ş
            if (path.size() == k && sum == targetSum) {
                result.push_back(path);
                return;
            }
            // »ØËİÂß¼­+¼ôÖ¦
            for (int i = startIndex; i <= 9 - (k - path.size()) + 1; i++) {
                path.push_back(i);
                sum += i;
                backtracking(k, targetSum, i + 1, sum);
                path.pop_back();
                sum -= i;
            }
        }
        vector<vector<int>> combinationSum3(int k, int n) {
            path.clear();
            result.clear();
            backtracking(k, n, 1, 0);
            return result;
        }
    };
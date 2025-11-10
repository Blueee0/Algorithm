class Solution {
    public:
        vector<vector<int>> result;
        vector<int> path;
        void backtracking(int n, int k, int startIndex) {
            // 终止条件
            if (path.size() == k) {
                result.push_back(path);
                return;
            }
    
            // 回溯逻辑
            for (int i = startIndex; i <= n - (k - path.size()) + 1; i++) {
                path.push_back(i);
                backtracking(n, k, i + 1);
                path.pop_back();
            }
        }
    
        vector<vector<int>> combine(int n, int k) {
            result.clear();
            path.clear();
            // 注意，集合是从1开始，所以startIndex是1
            backtracking(n, k, 1);
            return result;
        }
    };
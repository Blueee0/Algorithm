class Solution {
    public:
        int findMaxForm(vector<string>& strs, int m, int n) {
            vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    
            for (string str : strs) { // 遍历物品
                // 统计每个字符串的 0 和 1 的数量
                int x = 0, y = 0;
                for (char c : str) {
                    if (c == '0')
                        x++;
                    else
                        y++;
                }
                for (int i = m; i >= x; i--) { // 倒叙遍历背包
                    for (int j = n; j >= y; j--) {
                        dp[i][j] = max(dp[i][j], dp[i - x][j - y] + 1);
                    }
                }
            }
    
            return dp[m][n];
        }
    };
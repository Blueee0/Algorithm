class Solution {
    public:
        int longestCommonSubsequence(string text1, string text2) {
            int m = text1.size(), n = text2.size();
            vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    
            for (int i = 1; i <= m; i++) {
                for (int j = 1; j <= n; j++) {
                    // cout << "i = " << i << "\t" << "j = " << j << "\t";
                    if (text1[i - 1] == text2[j - 1]) {
                        dp[i][j] = dp[i - 1][j - 1] + 1;
                    } else {
                        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                    }
                    // cout << "dp[i][j] = " << dp[i][j] << "\n";
                }
            }
            return dp[m][n];
        }
    };
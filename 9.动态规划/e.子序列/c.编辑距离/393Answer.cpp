class Solution {
    public:
        bool isSubsequence(string s, string t) {
            int m = s.size(), n = t.size();
            vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    
            for (int i = 1; i <= m; i++) {
                for (int j = 1; j <= n; j++) {
                    // cout << "i = " << i << "\t" << "j = " << j << "\t";
                    if (s[i - 1] == t[j - 1]) {
                        dp[i][j] = dp[i - 1][j - 1] + 1;
                    } else {
                        dp[i][j] = dp[i][j - 1];
                    }
                    // cout << "dp[i][j] = " << dp[i][j] << "\n";
                }
            }
    
            if (dp[m][n] == s.size())
                return true;
            return false;
        }
    };
class Solution {
    public:
        int countSubstrings(string s) {
            int result = 0;
            int len = s.size();
            vector<vector<bool>> dp(len, vector<bool>(len, false));
    
            for (int i = len - 1; i >= 0; i--) {
                for (int j = i; j < len; j++) { // 注意j从i开始！
                    // cout << "i = " << i << "\t" << "j = " << j << "\t";
                    if (s[i] == s[j]) {
                        if (j - i <= 1) { // 情况一 和 情况二
                            result++;
                            dp[i][j] = true;
                        } else if (dp[i + 1][j - 1]) { // 情况三
                            result++;
                            dp[i][j] = true;
                        }
                    }
                    // cout << "dp[i][j] = " << dp[i][j] << "\n";
                }
            }
    
            return result;
        }
    };
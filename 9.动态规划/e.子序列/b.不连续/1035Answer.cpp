class Solution {
    public:
        int maxUncrossedLines(vector<int>& nums1, vector<int>& nums2) {
            int m = nums1.size(), n = nums2.size();
            vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    
            for (int i = 1; i <= m; i++) {
                for (int j = 1; j <= n; j++) {
                    // cout << "i = " << i << "\t" << "j = " << j << "\t";
                    if (nums1[i - 1] == nums2[j - 1]) {
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
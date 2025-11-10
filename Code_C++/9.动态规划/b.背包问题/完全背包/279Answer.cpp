class Solution {
    public:
        int numSquares(int n) {
            int bagWeight = n;
    
            vector<int> dp(bagWeight + 1, INT_MAX);
            dp[0] = 0;
    
            for (int i = 1; i*i <= n; i++) {
                for (int j = i*i; j <= bagWeight; j++) {
                    // 如果dp[j - i*i]是初始值则跳过，否则会越界
                    if (dp[j - i*i] != INT_MAX) {
                        dp[j] = min(dp[j - i*i] + 1, dp[j]);
                    }
                }
            }
            if (dp[n] == INT_MAX)
                return -1;
            return dp[n];
        }
    };
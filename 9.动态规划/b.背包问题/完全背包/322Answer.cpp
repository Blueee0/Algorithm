class Solution {
    public:
        int coinChange(vector<int>& coins, int amount) {
            int n = coins.size();
            int bagWeight = amount;
    
            vector<int> dp(bagWeight + 1, INT_MAX);
            dp[0] = 0;
    
            for (int i = 0; i < n; i++) {
                for (int j = coins[i]; j <= bagWeight; j++) {
                    // ���dp[j - coins[i]]�ǳ�ʼֵ�������������Խ��
                    if (dp[j - coins[i]] != INT_MAX) {
                        dp[j] = min(dp[j - coins[i]] + 1, dp[j]);
                    }
                }
            }
            if (dp[amount] == INT_MAX)
                return -1;
            return dp[amount];
        }
    };
class Solution {
    public:
        int maxProfit(vector<int>& prices) {
            int len = prices.size();
    
            if (len == 0)
                return 0;
    
            vector<vector<int>> dp(len, vector<int>(2));
            dp[0][0] -= prices[0];
            dp[0][1] = 0;
    
            for (int i = 1; i < len; i++) {
                // cout << "i = " << i << "\n";
                dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] - prices[i]);
                dp[i][1] = max(dp[i - 1][1], prices[i] + dp[i - 1][0]);
                // cout << "dp[i][0]= " << dp[i][0] << "\t" << "dp[i][1]=" << dp[i][1] << "\n";
            }
    
            // 卖出股票的钱 ＞ 持有股票的钱，所以打印dp[day-1][1]就可以
            return dp[len - 1][1];
        }
    };
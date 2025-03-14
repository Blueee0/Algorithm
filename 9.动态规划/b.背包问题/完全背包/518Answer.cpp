class Solution {
    public:
        int change(int amount, vector<int>& coins) {
            int n = coins.size();
            int bagWeight = amount;
    
            vector<int> dp(bagWeight + 1, 0);
            dp[0] = 1;
    
            for (int i = 0; i < n; i++) { // 遍历物品
                /* 打印当前物品
                cout << "放入物品i = " << i << "\t" << "\n";*/
                for (int j = coins[i]; j <= bagWeight; j++) { // 遍历背包容量
                    if (dp[j] < INT_MAX - dp[j - coins[i]]) { // 防止相加数据超int
                        dp[j] += dp[j - coins[i]];
                    }
    
                    /* 打印遍历过程
                    cout << "背包容量j = " << j << "\t"
                         << "最多方式dp[j] = " << dp[j] << "\n";*/
                }
            }
    
            /*打印最终的dp数组
            cout << "开始打印dp数组" << "\n";
            for (int i = 0; i < bagWeight; i++) {
                cout << "i = " << i << "\t" << "dp[i] = " << dp[i] << "\n";
            }*/
    
            return dp[bagWeight];
        }
    };
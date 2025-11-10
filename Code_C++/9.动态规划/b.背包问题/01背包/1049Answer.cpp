class Solution {
    public:
        int lastStoneWeightII(vector<int>& stones) {
            // 求和
            int sum = 0;
            for (int i = 0; i < stones.size(); i++) {
                sum += stones[i];
            }
    
            int item_num = stones.size();
            int begweight = sum / 2;
    
            vector<int> dp(begweight + 1, 0);
    
            for (int i = 0; i < item_num; i++) {
                for (int j = begweight; j >= stones[i]; j--) {
                    dp[j] = max(dp[j], dp[j - stones[i]] + stones[i]);
                }
            }
    
            /* 打印dp数组
            for (int i = 0; i < begweight + 1; i++) {
                cout << "i=" << i << '\t' << "dp[i]=" << dp[i] << '\n';
            }*/
    
            return sum - dp[begweight] * 2;
        }
    };
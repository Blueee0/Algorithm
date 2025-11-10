class Solution {
    public:
        int findTargetSumWays(vector<int>& nums, int target) {
            // 求和
            int sum = 0;
            for (int i = 0; i < nums.size(); i++) {
                sum += nums[i];
            }
            if (sum < abs(target) || (sum + target) % 2 == 1)
                return 0;
    
            // 背包
            int begweight = (sum + target) / 2;
            int item_num = nums.size();
            vector<int> dp(begweight + 1, 0);
            dp[0] = 1;
    
            for (int i = 0; i < item_num; i++) {
                for (int j = begweight; j >= nums[i]; j--) {
                    dp[j] += dp[j - nums[i]];
                }
            }
    
            /* 打印dp数组
            for (int i = 0; i < begweight + 1; i++) {
                cout << "i=" << i << '\t' << "dp[i]=" << dp[i] << '\n';
            }*/
    
            return dp[begweight];
        }
    };
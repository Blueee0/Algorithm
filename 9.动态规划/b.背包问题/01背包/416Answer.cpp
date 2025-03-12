class Solution {
    public:
        bool canPartition(vector<int>& nums) {
            // 求和
            int sum = 0;
            for (int i = 0; i < nums.size(); i++) {
                sum += nums[i];
            }
            if (sum % 2 == 1)
                return false;
    
            int item_num = nums.size();
            int begweight = sum / 2;
    
            vector<int> dp(begweight + 1, 0);
    
            for (int i = 0; i < item_num; i++) {
                for (int j = begweight; j >= nums[i]; j--) {
                    dp[j] = max(dp[j], dp[j - nums[i]] + nums[i]);
                }
            }
    
            /* 打印dp数组
            for (int i = 0; i < begweight + 1; i++) {
                cout << "i=" << i << '\t' << "dp[i]=" << dp[i] << '\n';
            }
            */
    
            if (dp[begweight] == begweight)
                return true;
            return false;
        }
    };
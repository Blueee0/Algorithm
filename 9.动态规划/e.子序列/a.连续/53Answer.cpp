class Solution {
    public:
        int maxSubArray(vector<int>& nums) {
            int n = nums.size();
            vector<int> dp(n + 1, 0);
            dp[0] = nums[0];
            int result = dp[0];
    
            for (int i = 1; i < nums.size(); i++) {
                // cout << "i = " << i << "\t";
                dp[i] = max(nums[i], dp[i - 1] + nums[i]);
                if (result < dp[i]) {
                    result = dp[i];
                }
                // cout << "dp[i] = " << dp[i] << "\n";
            }
            return result;
        }
    };
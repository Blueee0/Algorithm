class Solution {
    public:
        int lengthOfLIS(vector<int>& nums) {
            int n = nums.size();
            vector<int> dp(n, 1);
            int result = dp[0];
    
            for (int i = 1; i < nums.size(); i++) {
                // cout << "i = " << i << "\n";
                for (int j = 0; j < i; j++) {
                    if (nums[i] > nums[j]) {
                        dp[i] = max(dp[j] + 1, dp[i]);
                    }
                }
                if (dp[i] > result)
                    result = dp[i];
                // cout << "dp[i] = " << dp[i] << "\n";
            }
            return result;
        }
    };
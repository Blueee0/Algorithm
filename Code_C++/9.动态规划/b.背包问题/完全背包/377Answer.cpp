class Solution {
    public:
        int combinationSum4(vector<int>& nums, int target) {
            int n = nums.size();
            int bagWeight = target;
    
            vector<int> dp(bagWeight + 1, 0);
            dp[0] = 1;
    
            for (int j = 0; j <= bagWeight; j++) { // 遍历背包容量
                for (int i = 0; i < n; i++) {      // 遍历物品
                    if (j >= nums[i] && dp[j] < INT_MAX - dp[j - nums[i]])
                        dp[j] += dp[j - nums[i]];
                }
            }
    
            return dp[bagWeight];
        }
    };
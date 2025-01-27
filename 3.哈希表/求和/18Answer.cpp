class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> result;
        for (int k = 0; k < nums.size(); k++) {
            if (nums[k] > target && nums[k] >= 0) {
                break;
            }
            if (k > 0 && nums[k] == nums[k - 1]) {
                continue;
            }
            for (int i = k + 1; i < nums.size(); i++) {
                // 二级减枝
                if (nums[k] + nums[i] > target && nums[k] + nums[i] >= 0) {
                    break;
                }
                // 对nums[i]去重
                if (i > k + 1 && nums[i] == nums[i - 1]) {
                    continue;
                }
                int left = i + 1;
                int right = nums.size() - 1;
                while (right > left) {
                    if ((long)nums[k] + nums[i] + nums[left] + nums[right] >
                        target) {
                        right--;
                    } else if ((long)nums[k] + nums[i] + nums[left] +
                                   nums[right] <
                               target) {
                        left++;
                    } else {
                        result.push_back(vector<int>{nums[k], nums[i],
                                                     nums[left], nums[right]});
                        while (right > left && nums[right] == nums[right - 1]) {
                            right--;
                        }
                        while (right > left && nums[left] == nums[left + 1]) {
                            left++;
                        }
                        right--;
                        left++;
                    }
                }
            }
        }
        return result;
    }
};
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end()); // ������

        int i = 0, left = 1, right = nums.size();
        for (i = 0; i < nums.size(); i++) {
            // ����֮�������һ��Ԫ���Ѿ������㣬��ô���������϶������ܴճ���Ԫ�飬ֱ�ӷ��ؽ���Ϳ�����
            if (nums[i] > 0) {
                return result;
            }

            // ȥ�أ�ȷ���ҵ���ͬ����Ԫ��
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }
            left = i + 1;
            right = nums.size() - 1;

            while (right > left) {
                if (nums[i] + nums[left] + nums[right] > 0) {
                    right--;
                } else if (nums[i] + nums[left] + nums[right] < 0) {
                    left++;
                } else {
                    result.push_back(
                        vector<int>{nums[i], nums[left], nums[right]});

                    // ȥ���߼�Ӧ�÷����ҵ�һ����Ԫ��֮�󣬶�b �� cȥ��
                    while (right > left && nums[right] == nums[right - 1])
                        right--;
                    while (right > left && nums[left] == nums[left + 1])
                        left++;

                    // �ҵ���ʱ��˫ָ��ͬʱ����
                    right--;
                    left++;
                }
            }
        }
        return result;
    }
};
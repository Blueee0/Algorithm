class Solution {
    public:
        vector<vector<int>> result;
        vector<int> path;
    
        void backtracking(vector<int>& nums, vector<bool> used) {
            if (path.size() == nums.size()) {
                result.push_back(path);
                return;
            }
            for (int i = 0; i < nums.size(); i++) {
                // ȥ��
                // used[i - 1] == true��˵��ͬһ��֦nums[i - 1]ʹ�ù�
                // used[i - 1] == false��˵��ͬһ����nums[i - 1]ʹ�ù�
                if (i > 0 && nums[i] == nums[i - 1] && used[i - 1] == false) {
                    continue;
                }
                // ���У������used[i]==true�����
                if (used[i] == false) {
                    used[i] = true;
                    path.push_back(nums[i]);
                    backtracking(nums, used);
                    path.pop_back();
                    used[i] = false;
                }
            }
        }
    
        vector<vector<int>> permuteUnique(vector<int>& nums) {
            result.clear();
            path.clear();
            vector<bool> used(nums.size(), false);
            sort(nums.begin(), nums.end());
            backtracking(nums, used);
            return result;
        }
    };
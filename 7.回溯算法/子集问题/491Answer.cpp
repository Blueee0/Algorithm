class Solution {
    public:
        vector<vector<int>> result;
        vector<int> path;
    
        void backtracking(vector<int>& nums, int startIndex) {
            if (path.size() >= 2) {
                result.push_back(path);
                // ע�⣡���ﲻҪ��return��Ҫȡ���ϵĽڵ�
            }
            unordered_set<int> uset; // ʹ��set�Ա���Ԫ�ؽ���ȥ��
            for (int i = startIndex; i < nums.size(); i++) {
                if ((!path.empty() && nums[i] < path.back()) || uset.find(nums[i]) != uset.end()) {
                    // ��path��Ϊ��ʱ������ȡԪ��С��path��β�������ɷǵݼ���������Ҫ����ݹ�
                    // �����ֵ�ǰȡ�����ڱ������Ѿ����ù���������ݹ�
                    continue;
                }
                uset.insert(nums[i]); // ��¼Ԫ�ر�ʹ�ù�
                path.push_back(nums[i]);
                backtracking(nums, i + 1);
                path.pop_back();
            }
            return;
        }
    
        vector<vector<int>> findSubsequences(vector<int>& nums) {
            result.clear();
            path.clear();
            backtracking(nums, 0);
            return result;
        }
    };
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> map;    // first��key��second��value
        int s = 0;
        for (int i = 0; i < nums.size(); i++) {
            // ������ǰԪ�أ�����map��Ѱ���Ƿ���ƥ���key
            auto iter = map.find(target - nums[i]);
            if (iter != map.end()) {
                return {iter->second, i};
            }
            // ���û�ҵ�ƥ��ԣ��Ͱѷ��ʹ���Ԫ�غ��±���뵽map��
            map.insert(pair<int, int>(nums[i], i));
        }
        return {};
    }
};
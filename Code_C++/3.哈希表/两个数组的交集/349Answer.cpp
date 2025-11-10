class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> result;
        unordered_set<int> num_set(nums1.begin(), nums1.end());// 把nums1输入哈希表

        for (int i = 0; i < nums2.size(); i++) {
            // 发现nums2的元素 在num_set里有出现过
            if (num_set.find(nums2[i]) != num_set.end()) {
                result.insert(nums2[i]);
            }
        }
        return vector<int>(result.begin(), result.end());
    }
};
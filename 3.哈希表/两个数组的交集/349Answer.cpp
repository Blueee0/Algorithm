class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> result;
        unordered_set<int> num_set(nums1.begin(), nums1.end());// ��nums1�����ϣ��

        for (int i = 0; i < nums2.size(); i++) {
            // ����nums2��Ԫ�� ��num_set���г��ֹ�
            if (num_set.find(nums2[i]) != num_set.end()) {
                result.insert(nums2[i]);
            }
        }
        return vector<int>(result.begin(), result.end());
    }
};
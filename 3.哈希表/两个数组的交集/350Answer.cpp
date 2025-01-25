class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        int hash[1001] = {0};
        multiset<int> result;
        int i = 0;
        for (i = 0; i < nums1.size(); i++) {
            hash[nums1[i]]++;
        }
        for (i = 0; i < nums2.size(); i++) {
            if (hash[nums2[i]] > 0) {
                result.insert(nums2[i]);
                hash[nums2[i]]--;
            }
        }
        return vector<int>(result.begin(), result.end());
    }
};
class Solution {
public:
    int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3,
                     vector<int>& nums4) {
        unordered_map<int, int> map;    //key:a+b的数值，value:a+b数值出现的次数
        int a = 0, b = 0, c = 0, d = 0, s = 0, cnt = 0;
        // 在map中存下所有a+b的可能和对应的次数
        for (int i = 0; i < nums1.size(); i++) {
            for (int j = 0; j < nums2.size(); j++) {
                a = nums1[i];
                b = nums2[j];
                map[a + b]++;
            }
        }
        // 遍历c+d的所有可能，查找所需的a+b
        for (int i = 0; i < nums3.size(); i++) {
            for (int j = 0; j < nums4.size(); j++) {
                c = nums3[i];
                d = nums4[j];
                s = 0 - (c + d);
                if (map.find(s) != map.end()) {
                    cnt = cnt + map[s]; // 注意cnt不是单纯加一！
                }
            }
        }
        return cnt;
    }
};
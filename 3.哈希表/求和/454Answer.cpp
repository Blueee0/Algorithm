class Solution {
public:
    int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3,
                     vector<int>& nums4) {
        unordered_map<int, int> map;    //key:a+b����ֵ��value:a+b��ֵ���ֵĴ���
        int a = 0, b = 0, c = 0, d = 0, s = 0, cnt = 0;
        // ��map�д�������a+b�Ŀ��ܺͶ�Ӧ�Ĵ���
        for (int i = 0; i < nums1.size(); i++) {
            for (int j = 0; j < nums2.size(); j++) {
                a = nums1[i];
                b = nums2[j];
                map[a + b]++;
            }
        }
        // ����c+d�����п��ܣ����������a+b
        for (int i = 0; i < nums3.size(); i++) {
            for (int j = 0; j < nums4.size(); j++) {
                c = nums3[i];
                d = nums4[j];
                s = 0 - (c + d);
                if (map.find(s) != map.end()) {
                    cnt = cnt + map[s]; // ע��cnt���ǵ�����һ��
                }
            }
        }
        return cnt;
    }
};
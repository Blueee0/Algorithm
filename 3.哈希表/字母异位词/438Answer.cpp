class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int sLen = s.size(), pLen = p.size();
        if (sLen < pLen) {
            return vector<int>();
        }

        vector<int> ans;
        int sHash[26] = {0};
        int pHash[26] = {0};

        // ��¼�ַ���p�ͳ�ʼ���ַ���s
        for (int i = 0; i < p.size(); i++) {
            pHash[p[i] - 'a']++;
            sHash[s[i] - 'a']++;
        }

        // ���ַ���s��ά����������
        for (int i = 0; i < sLen - pLen; i++) {
            if (memcmp(sHash, pHash, sizeof(sHash)) == 0) {
                ans.emplace_back(i);
            }
            sHash[s[i] - 'a']--;
            sHash[s[i + pLen] - 'a']++;
        }
        // ע�⣬���һ��ҲҪ�жϣ���i = sLen - pLen��ʱ�򣬲������ƶ��ַ���������Ҫ�ж��Ƿ����
        if (memcmp(sHash, pHash, sizeof(sHash)) == 0) {
            ans.emplace_back(sLen - pLen);
        }
        return ans;
    }
};
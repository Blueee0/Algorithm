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

        // 记录字符串p和初始的字符串s
        for (int i = 0; i < p.size(); i++) {
            pHash[p[i] - 'a']++;
            sHash[s[i] - 'a']++;
        }

        // 在字符串s中维护滑动窗口
        for (int i = 0; i < sLen - pLen; i++) {
            if (memcmp(sHash, pHash, sizeof(sHash)) == 0) {
                ans.emplace_back(i);
            }
            sHash[s[i] - 'a']--;
            sHash[s[i + pLen] - 'a']++;
        }
        // 注意，最后一个也要判断，当i = sLen - pLen的时候，不可以移动字符串，但是要判断是否相等
        if (memcmp(sHash, pHash, sizeof(sHash)) == 0) {
            ans.emplace_back(sLen - pLen);
        }
        return ans;
    }
};
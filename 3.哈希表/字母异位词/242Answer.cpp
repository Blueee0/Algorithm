class Solution {
public:
    bool isAnagram(string s, string t) {
        int hash[26]={0};
        int i = 0;
        // 标记字符串s所有字母出现的频率
        for (i = 0; i < s.size(); i++) {
            hash[s[i] - 'a']++;
        }
        for (i = 0; i < t.size(); i++) {
            hash[t[i] - 'a']--;
        }
        for (i = 0; i < 26; i++) {
            if (hash[i] != 0)
                return false;
        }
        return true;
    }
};
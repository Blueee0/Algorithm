class Solution {
public:
    void getNext(int* next, const string& s) {
        // j前缀末尾；i后缀末尾
        int j = 0, i = 1;
        next[0] = 0;

        // 判断最长相等前后缀，并且更新next数组
        for (i = 1; i < s.size(); i++) {
            // 当前后缀不相等时，回退j（j=0时，不回退）
            while (j > 0 && s[i] != s[j])
                j = next[j - 1];

            // 当前后缀相等时，更新j
            if (s[i] == s[j])
                j++;

            // 更新next数组
            next[i] = j;
        }
    }

    int strStr(string haystack, string needle) {
        // 处理模式串长度为0的情况
        if (needle.size() == 0) {
            return 0;
        }

        // 获取前缀表
        vector<int> next(needle.size());
        getNext(&next[0], needle);

        int j = 0;
        for (int i = 0; i < haystack.size(); i++) {
            // 如果字符串不匹配，利用前缀表获取返回的位置
            while (j > 0 && haystack[i] != needle[j]) {
                j = next[j - 1];
            }
            // 如果字符串匹配，继续移动j
            if (haystack[i] == needle[j]) {
                j++;
            }
            // 如果字符串匹配完毕，返回第一个匹配项下标
            if (j == needle.size()) {
                return (i - needle.size() + 1);
            }
        }
        return -1;
    }
};
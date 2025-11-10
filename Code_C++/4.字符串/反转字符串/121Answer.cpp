class Solution {
public:
    // 反转字符串s中左闭右闭的区间[start, end]
    void reverse(string& s, int start, int end) {
        for (int i = start, j = end; i < j; i++, j--) {
            swap(s[i], s[j]);
        }
    }

    void removeExtraSpaces(string& s) { // 去除空格
        int slow = 0,
            fast = 0; // fast指向符合题目要求的字母，slow指向需要更改的地方
        for (fast = 0; fast < s.size(); fast++) {
            if (s[fast] != ' ') {
                if (slow != 0) { // 如果slow指向第一个单词，不需要留空格
                    s[slow] = ' ';
                    slow++;
                }
                while (fast < s.size() && s[fast] != ' ') {
                    s[slow] = s[fast];
                    fast++;
                    slow++;
                }
            }
        }
        s.resize(slow); // slow的大小即为去除多余空格后的大小。
    }

    string reverseWords(string s) {
        removeExtraSpaces(
            s); // 去除多余空格，保证单词之间之只有一个空格，且字符串首尾没空格。
        reverse(s, 0, s.size() - 1);
        int start = 0; // removeExtraSpaces后保证第一个单词的开始下标一定是0。
        for (int i = 0; i <= s.size(); ++i) {
            if (i == s.size() ||
                s[i] == ' ') { // 到达空格或者串尾，说明一个单词结束。进行翻转。
                reverse(s, start, i - 1); // 翻转，注意是左闭右闭 []的翻转。
                start = i + 1; // 更新下一个单词的开始下标start
            }
        }
        return s;
    }
};
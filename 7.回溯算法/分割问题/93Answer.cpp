class Solution {
    public:
        vector<string> result;
    
        void backtracking(string& s, int startIndex, int times) {
            // 用times表示进行到第几个循环，进入第四个循环就return
            if (times == 4) {
                // 判断第四段子字符串是否合法，如果合法就放进result中
                if (isValid(s, startIndex, s.size() - 1)) {
                    result.push_back(s);
                }
                return;
            }
    
            for (int i = startIndex; i < s.size(); i++) {
                // 如果字符串合法，则继续递归；否则不需要进入递归
                if (isValid(s, startIndex, i)) {
                    s.insert(s.begin() + i + 1, '.');
                    backtracking(s, i + 2, times + 1);
                    s.erase(s.begin() + i + 1);
                } else {
                    continue;
                }
            }
        }
    
        /* 判断当前字段是否合法
            - 段位以0为开头的数字不合法
            - 段位里有非正整数字符不合法
            - 段位如果大于255了不合法
        */
        bool isValid(const string& s, int start, int end) {
            if (start > end) {
                return false;
            }
    
            // 0开头的数字不合法
            if (s[start] == '0' && start != end) {
                return false;
            }
    
            int num = 0;
            for (int i = start; i <= end; i++) {
                // 遇到非数字字符不合法
                if (s[i] > '9' || s[i] < '0') {
                    return false;
                }
    
                // 如果大于255了不合法
                num = num * 10 + (s[i] - '0');
                if (num > 255) {
                    return false;
                }
            }
            return true;
        }
    
        vector<string> restoreIpAddresses(string s) {
            result.clear();
            // 剪枝：s的长度在[4,12]
            if (s.size() < 4 || s.size() > 12)
                return result;
            backtracking(s, 0, 1);
            return result;
        }
    };
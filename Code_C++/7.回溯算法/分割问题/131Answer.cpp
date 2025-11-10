class Solution {
    public:
        vector<vector<string>> result;
        vector<string> path;
    
        void backtracking(const string& s, int startIndex) {
            if (startIndex == s.size()) {
                result.push_back(path);
                return;
            }
    
            for (int i = startIndex; i < s.size(); i++) {
                // isPalindrome判断是否是回文子串，[startIndex, i]
                if (isPalindrome(s, startIndex, i)) {
                    // 如果是回文子串，则放入path，然后进入递归
                    string str = s.substr(startIndex, i - startIndex + 1);
                    path.push_back(str);
                } else {
                    // 如果不是回文子串，则不需要进入递归
                    continue;
                }
                backtracking(s, i + 1);
                path.pop_back();
            }
        }
    
        // isPalindrome判断是否是回文子串
        bool isPalindrome(const string& s, int start, int end) {
            // 从起始和终点，同时向内遍历
            for (int i = start, j = end; i < j; i++, j--) {
                if (s[i] != s[j]) {
                    return false;
                }
            }
            return true;
        }
    
        vector<vector<string>> partition(string s) {
            path.clear();
            result.clear();
            backtracking(s, 0);
            return result;
        }
    };
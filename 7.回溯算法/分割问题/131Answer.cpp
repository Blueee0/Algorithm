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
                // isPalindrome�ж��Ƿ��ǻ����Ӵ���[startIndex, i]
                if (isPalindrome(s, startIndex, i)) {
                    // ����ǻ����Ӵ��������path��Ȼ�����ݹ�
                    string str = s.substr(startIndex, i - startIndex + 1);
                    path.push_back(str);
                } else {
                    // ������ǻ����Ӵ�������Ҫ����ݹ�
                    continue;
                }
                backtracking(s, i + 1);
                path.pop_back();
            }
        }
    
        // isPalindrome�ж��Ƿ��ǻ����Ӵ�
        bool isPalindrome(const string& s, int start, int end) {
            // ����ʼ���յ㣬ͬʱ���ڱ���
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
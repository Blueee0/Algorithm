class Solution {
    private:
        const string letterMap[10] = {
            "",     // 0
            "",     // 1
            "abc",  // 2
            "def",  // 3
            "ghi",  // 4
            "jkl",  // 5
            "mno",  // 6
            "pqrs", // 7
            "tuv",  // 8
            "wxyz", // 9
        };
    
    public:
        string ans;
        vector<string> result;
    
        void backtracking(string& digits, int index) {
            // 终止条件，处理完字符串中的最后一个数字后，结束
            if (index == digits.size()) {
                result.push_back(ans);
                return;
            }
    
            // index 表示本层处理的字符串中的数字下标是多少（在处理第几个数字）
            int digit = digits[index] - '0';  // 当前取到的数字
            string letter = letterMap[digit]; // 数字对应的字母集合
            for (int i = 0; i < letter.size(); i++) {
                ans.push_back(letter[i]);
                backtracking(digits, index + 1);
                ans.pop_back();
            }
        }
    
        vector<string> letterCombinations(string digits) {
            ans.clear();
            result.clear();
            if (digits.size() == 0) {
                return result;
            }
            backtracking(digits, 0);
            return result;
        }
    };
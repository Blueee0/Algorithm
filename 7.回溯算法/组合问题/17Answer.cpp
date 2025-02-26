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
            // ��ֹ�������������ַ����е����һ�����ֺ󣬽���
            if (index == digits.size()) {
                result.push_back(ans);
                return;
            }
    
            // index ��ʾ���㴦����ַ����е������±��Ƕ��٣��ڴ���ڼ������֣�
            int digit = digits[index] - '0';  // ��ǰȡ��������
            string letter = letterMap[digit]; // ���ֶ�Ӧ����ĸ����
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
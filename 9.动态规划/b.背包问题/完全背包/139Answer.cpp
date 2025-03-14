class Solution {
    public:
        bool wordBreak(string s, vector<string>& wordDict) {
            unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
    
            vector<bool> dp(s.size() + 1, false);
            dp[0] = true;
            
            for (int i = 1; i <= s.size(); i++) { // ��������
                for (int j = 0; j < i; j++) {     // ������Ʒ
                    string word = s.substr(j, i - j); // substr(��ʼλ�ã���ȡ�ĸ���)
                    if (wordSet.find(word) != wordSet.end() && dp[j]) {
                        dp[i] = true;
                    }
                }
            }
            return dp[s.size()];
        }
    };
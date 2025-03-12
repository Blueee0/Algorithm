class Solution {
    public:
        int findMaxForm(vector<string>& strs, int m, int n) {
            vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    
            for (string str : strs) { // ������Ʒ
                // ͳ��ÿ���ַ����� 0 �� 1 ������
                int x = 0, y = 0;
                for (char c : str) {
                    if (c == '0')
                        x++;
                    else
                        y++;
                }
                for (int i = m; i >= x; i--) { // �����������
                    for (int j = n; j >= y; j--) {
                        dp[i][j] = max(dp[i][j], dp[i - x][j - y] + 1);
                    }
                }
            }
    
            return dp[m][n];
        }
    };
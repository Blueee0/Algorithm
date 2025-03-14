class Solution {
    public:
        int change(int amount, vector<int>& coins) {
            int n = coins.size();
            int bagWeight = amount;
    
            vector<int> dp(bagWeight + 1, 0);
            dp[0] = 1;
    
            for (int i = 0; i < n; i++) { // ������Ʒ
                /* ��ӡ��ǰ��Ʒ
                cout << "������Ʒi = " << i << "\t" << "\n";*/
                for (int j = coins[i]; j <= bagWeight; j++) { // ������������
                    if (dp[j] < INT_MAX - dp[j - coins[i]]) { // ��ֹ������ݳ�int
                        dp[j] += dp[j - coins[i]];
                    }
    
                    /* ��ӡ��������
                    cout << "��������j = " << j << "\t"
                         << "��෽ʽdp[j] = " << dp[j] << "\n";*/
                }
            }
    
            /*��ӡ���յ�dp����
            cout << "��ʼ��ӡdp����" << "\n";
            for (int i = 0; i < bagWeight; i++) {
                cout << "i = " << i << "\t" << "dp[i] = " << dp[i] << "\n";
            }*/
    
            return dp[bagWeight];
        }
    };
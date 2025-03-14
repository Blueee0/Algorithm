#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n, bagweight;   // ��Ʒ����n����������begweight
    cin >> n >> bagweight;

    vector<int> value(n),weight(n);   // ��Ʒ��ֵ������
    for (int i = 0; i < n; i++) {
        cin >> weight[i] >> value[i];
    }

    // ��ʼ��dp����
    vector<vector<int>> dp(n, vector<int>(bagweight + 1, 0));
    for(int j = weight[0]; j <= bagweight; j++){
        // һֱװvalue[0]��ֱ��װ��
        dp[0][j] = dp[0][j-weight[0]] + value[0];
    }

    for(int i = 1; i < n ; i++){
        for(int j = 0; j <= bagweight ; j++){
            if (j < weight[i]) 
                dp[i][j] = dp[i - 1][j];
            else 
                dp[i][j] = max(dp[i - 1][j], dp[i][j - weight[i]] + value[i]);
        }
    }

    cout << dp[n-1][bagweight];
    
    return 0;
}
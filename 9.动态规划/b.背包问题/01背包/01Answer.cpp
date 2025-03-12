#include <bits/stdc++.h>
using namespace std;

int main(){
    int n, beg;
    cin >> n >> beg;

    vector<int> weight(n,0);    // ��Ų��ϵ�����
    vector<int> value(n,0);     // ��Ų��ϵļ�ֵ

    for(int i = 0; i < n; i++){
        cin >> weight[i];
    }

    for(int i = 0; i < n; i++){
        cin >> value[i];
    }

    // ��Ʒ����n��0-n-1������������0��beg
    vector<vector<int>> dp(n,vector<int>(beg+1,0)); 

    // ��ʼ�� dp[0][j]
    for(int j = weight[0]; j <= beg; j++){
            dp[0][j] = value[0];
    }

    // ����
    for(int i = 1; i < n; i++){     // ������Ʒ
        for(int j = 1; j <= beg; j++){ // ������������
            if( j < weight[i] ){
                // ���װ������Ʒ���ͼ̳�
                dp[i][j] = dp[i - 1][j];
            }else{
                // ���װ������Ʒ����ȡmax
                dp[i][j] = max(dp[i-1][j],dp[i-1][j-weight[i]]+value[i]);
            }
        }
    }

    // �������Ʒ����n-1����������beg
    cout << dp[n-1][beg];
    return 0;
}
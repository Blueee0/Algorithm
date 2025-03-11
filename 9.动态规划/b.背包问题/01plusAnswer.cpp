#include <iostream>
#include <vector>
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

    // ��������0��beg
    vector<int> dp(beg+1,0); 

    // ����
    for(int i = 0; i < n; i++){     // ������Ʒ
        for(int j = beg; j >= weight[i]; j--){ // ���������������
            dp[j] = max(dp[j],dp[j-weight[i]]+value[i]);
        }
    }

    // �������������beg
    cout << dp[beg];
    return 0;
}
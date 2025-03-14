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
    vector<int> dp(bagweight + 1, 0);

    cout << "�鿴һάdp����ѭ��" << "\n";
    for(int i = 0; i < n ; i++){
        cout << "������Ʒi = " << i << "\t" << "\n" ; 
        for(int j = 0; j <= bagweight ; j++){
            if (j >= weight[i]){
                dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
            }
            cout << "��������j = " << j << "\t" << "����ֵdp[j] = " << dp[j]  << "\n" ; 
        }
    }

    // ��ӡ���յ�dp����
    cout << "��ʼ��ӡdp����"  << "\n";
    for(int i = 0; i < bagweight ; i++){
        cout << "i = " << i << "\t" << "dp[i] = " << dp[i] << "\n"; 
    }

    // ������
    cout << "������";
    cout << dp[bagweight];
    
    return 0;
}
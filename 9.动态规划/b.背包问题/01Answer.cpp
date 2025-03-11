#include <bits/stdc++.h>
using namespace std;

int main(){
    int n, beg;
    cin >> n >> beg;

    vector<int> weight(n,0);    // 存放材料的重量
    vector<int> value(n,0);     // 存放材料的价值

    for(int i = 0; i < n; i++){
        cin >> weight[i];
    }

    for(int i = 0; i < n; i++){
        cin >> value[i];
    }

    // 物品数量n（0-n-1），背包容量0到beg
    vector<vector<int>> dp(n,vector<int>(beg+1,0)); 

    // 初始化 dp[0][j]
    for(int j = weight[0]; j <= beg; j++){
            dp[0][j] = value[0];
    }

    // 递推
    for(int i = 1; i < n; i++){     // 遍历物品
        for(int j = 1; j <= beg; j++){ // 遍历背包容量
            if( j < weight[i] ){
                // 如果装不下物品，就继承
                dp[i][j] = dp[i - 1][j];
            }else{
                // 如果装得下物品，就取max
                dp[i][j] = max(dp[i-1][j],dp[i-1][j-weight[i]]+value[i]);
            }
        }
    }

    // 输出：物品种类n-1，背包容量beg
    cout << dp[n-1][beg];
    return 0;
}
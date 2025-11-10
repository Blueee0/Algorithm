#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n, bagweight;   // 物品种类n，背包容量begweight
    cin >> n >> bagweight;

    vector<int> value(n),weight(n);   // 物品价值和重量
    for (int i = 0; i < n; i++) {
        cin >> weight[i] >> value[i];
    }

    // 初始化dp数组
    vector<vector<int>> dp(n, vector<int>(bagweight + 1, 0));
    for(int j = weight[0]; j <= bagweight; j++){
        // 一直装value[0]，直到装满
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
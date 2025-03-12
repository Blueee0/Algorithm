#include <iostream>
#include <vector>
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

    // 背包容量0到beg
    vector<int> dp(beg+1,0); 

    // 递推
    for(int i = 0; i < n; i++){     // 遍历物品
        for(int j = beg; j >= weight[i]; j--){ // 倒叙遍历背包容量
            dp[j] = max(dp[j],dp[j-weight[i]]+value[i]);
        }
    }

    // 输出：背包容量beg
    cout << dp[beg];
    return 0;
}
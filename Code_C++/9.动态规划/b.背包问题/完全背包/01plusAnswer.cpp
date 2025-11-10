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
    vector<int> dp(bagweight + 1, 0);

    cout << "查看一维dp数组循环" << "\n";
    for(int i = 0; i < n ; i++){
        cout << "放入物品i = " << i << "\t" << "\n" ; 
        for(int j = 0; j <= bagweight ; j++){
            if (j >= weight[i]){
                dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
            }
            cout << "背包容量j = " << j << "\t" << "最大价值dp[j] = " << dp[j]  << "\n" ; 
        }
    }

    // 打印最终的dp数组
    cout << "开始打印dp数组"  << "\n";
    for(int i = 0; i < bagweight ; i++){
        cout << "i = " << i << "\t" << "dp[i] = " << dp[i] << "\n"; 
    }

    // 输出结果
    cout << "输出结果";
    cout << dp[bagweight];
    
    return 0;
}
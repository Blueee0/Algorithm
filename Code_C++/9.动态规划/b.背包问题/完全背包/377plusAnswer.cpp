#include <iostream>
#include <vector>
using namespace std;

int main(){
    int bagWeight,n;
    cin >> bagWeight >> n;

    vector<int> dp(bagWeight+1,0);
    dp[0] = 1;

    for(int j = 0;j <= bagWeight;j++){
        for(int i = 1;i < n+1;i++){
            if( j >= i ){
                dp[j] += dp[j-i];
            }
        }
    }

    cout << dp[bagWeight];
    return 0;
}

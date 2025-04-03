#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main(){

    int n, m, s, e, val;
    cin >> n >> m;
    vector<vector<int>> grid(n + 1, vector<int>(n + 1, INT_MAX));
    while(m--){
        cin >> s >> e >> val;
        grid[s][e] = val;
    }
    int start = 1, end = n;
    
    // 记录非访问节点到源点的距离
    vector<int> minDist(n + 1, INT_MAX);
    minDist[start] = 0;

    // 记录访问过的节点
    vector<bool> visited(n + 1, false);
    
    // 遍历所有节点
    for(int i = 1; i <= n; i++){
        // 第一步，选源点到哪个节点近且该节点未被访问过
        int minVal = INT_MAX;
        int cur = 1;
        for (int j = 1; j <= n; j++){
            if(!visited[j] && minDist[j] < minVal){
                minVal = minDist[j];
                cur = j;
            }
        }

        // 第二步，该最近节点被标记访问过
        visited[cur] = true;


        // 第三步，更新非访问节点到源点的距离（即更新minDist数组）
        for(int j = 1; j <= n; j++){
            if(!visited[j] && grid[cur][j] != INT_MAX && minDist[cur] + grid[cur][j] < minDist[j]){
                minDist[j] = minDist[cur] + grid[cur][j];
            }
        }
    }
    if (minDist[end] == INT_MAX)    // 不能到达终点
        cout << -1 << endl; 
    else 
        cout << minDist[end] << endl; // 到达终点最短路径


    return 0;
}
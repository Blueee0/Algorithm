#include <iostream>
#include <vector>
#include <list>
#include <climits>
using namespace std;

int main(){
    int n, m, s, t, val;
    cin >> n >> m;
    vector<vector<int>> umap; 
    for(int i = 0; i < m; i++){
        cin >> s >> t >> val;
        umap.push_back({s, t, val});
    }

    int start = 1, end = n;
    vector<int> minDist(n + 1, INT_MAX);
    minDist[start] = 0;
    for(int i = 0; i < n - 1; i++){
        for(vector<int> &side : umap){
            int from = side[0];
            int to = side[1];
            int value = side[2];
            // minDist[from] != INT_MAX 防止从未计算过的节点出发
            if(minDist[from] != INT_MAX && minDist[to] > minDist[from] + value){
                minDist[to] = minDist[from] + value;
            }
        }
    }

    if (minDist[end] == INT_MAX) 
        cout << "unconnected" << endl; // 不能到达终点
    else 
        cout << minDist[end] << endl; // 到达终点最短路径长度
}
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
    bool flag = false;
    for(int i = 1; i <= n; i++){
        for(vector<int> &side : umap){
            int from = side[0];
            int to = side[1];
            int value = side[2];
            if (i < n) {
                if (minDist[from] != INT_MAX && minDist[to] > minDist[from] + value) minDist[to] = minDist[from] + value;
            } else { // 多加一次松弛判断负权回路
                if (minDist[from] != INT_MAX && minDist[to] > minDist[from] + value) flag = true;
            }
        }
    }

    if (flag) {
        cout << "circle" << endl;
    } else if (minDist[end] == INT_MAX) {
        cout << "unconnected" << endl;
    } else {
        cout << minDist[end] << endl;
    }

    return 0;
}
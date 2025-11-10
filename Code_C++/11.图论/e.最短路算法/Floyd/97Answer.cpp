#include <iostream>
#include <vector>
#include <list>
using namespace std;

int main(){
    int n, m, u, v, val;
    cin >> n >> m;

    vector<vector<vector<int>>> grid(n + 1, vector<vector<int>>(n + 1, vector<int>(n + 1, 10005)));  // 因为边的最大距离是10^4
    for(int i = 0; i < m; i++){
        cin >> u >> v >> val;
        grid[u][v][0] = val;
        grid[v][u][0] = val;
    }

    // floyd
    for(int k = 1; k <= n; k++){
        for(int j = 1; j <= n; j++){
            for(int i = 1; i <= n; i++){
                grid[i][j][k] = min(grid[i][k][k - 1] + grid[k][j][k - 1], grid[i][j][k - 1]);
            }
        }
    }

    int q, start, end;
    cin >> q;
    while (q--) {
        cin >> start >> end;
        if (grid[start][end][n] == 10005) 
            cout << -1 << endl;
        else 
            cout << grid[start][end][n] << endl;
    }

    return 0;
}
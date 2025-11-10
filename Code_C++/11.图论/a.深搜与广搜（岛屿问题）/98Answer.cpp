#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> result;
vector<int> path;

void dfs(const vector<vector<int>>& graph, int x, int n){
    // 当前遍历的节点x 到达节点n 
    if (x == n) {   // 找到符合条件的一条路径
        result.push_back(path);
        return;
    }

    for (int i = 1; i <= n; i++) {  // 遍历节点x链接的所有节点
        if (graph[x][i] == 1) {     // 找到 x链接的节点
            path.push_back(i);      // 遍历到的节点加入到路径中来
            dfs(graph, i, n);       // 进入下一层递归
            path.pop_back();        // 回溯，撤销本节点
        }
    }
}


int main() {
    int n, m, i, j;
    cin >> n >> m; // 输入n个节点，m条边
    vector<vector<int>> graph(n + 1, vector<int>(n + 1, 0));

    while (m--) {
        cin >> i >> j;
        graph[i][j] = 1;
    }

    path.push_back(1);
    dfs(graph, 1, n);

    // 输出结果
    if (result.size() == 0) cout << -1 << endl;

    for (const vector<int> &pa : result) {
        for (int i = 0; i < pa.size() - 1; i++) {
            cout << pa[i] << " ";
        }
        cout << pa[pa.size() - 1]  << endl;
    }

    return 0;
}
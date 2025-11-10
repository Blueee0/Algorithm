#include <iostream>
#include <vector>
#include <list>
using namespace std;

void dfs(const vector<list<int>>& graph, vector<bool>& visited, int key){
    if(visited[key])
        return;
    visited[key] = true;
    list<int> keys = graph[key];
    for(int i : keys){
        dfs(graph, visited, i);
    }

}

int main(){
    int n, k;
    cin >> n >> k;

    // 使用邻接表读取graph
    vector<list<int>> graph(n + 1); // 邻接表
    for(int i = 0; i < k; i++){
        int s, t;
        cin >> s >> t;
        graph[s].push_back(t);
    }

    vector<bool> visited(n + 1, false); // 记录是否被访问过
    dfs(graph, visited, 1);
    for(int i = 1; i < n + 1; i++){
        if(visited[i] == false){
            cout << -1 << endl;
            return 0;
        }
    }

    cout << 1 << endl;
    return 0;
}
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

int main(){
    int m, n, s, t;
    cin >> n >> m;
    vector<int> inDegree(n, 0); // 记录入度
    vector<int> result; // 记录结果
    unordered_map<int, vector<int>> umap; // 记录文件依赖关系

    while(m--){
        cin >> s >> t;
        inDegree[t]++;
        umap[s].push_back(t);
    }

    // 初始化存储入度为0的点
    queue<int> que;
    for (int i = 0; i < n; i++) {
        if (inDegree[i] == 0) 
            que.push(i);
    }

    // 记录结果
    while (que.size()) {
        int cur = que.front();
        que.pop();
        result.push_back(cur);

        // 将该节点从图中移除：该节点作为出发点所连接的节点的 入度 减一
        vector<int> files = umap[cur];
        if (files.size()) { 
            for (int i = 0; i < files.size(); i++) {
                inDegree[files[i]] --; // cur指向的节点入度都做减一操作
                // 如果指向的节点减一之后，入度为0，说明是要选取的下一个节点，放入队列。
                if(inDegree[files[i]] == 0) 
                    que.push(files[i]); 
            }
        }
    }

    if (result.size() == n) {
        for (int i = 0; i < n - 1; i++) 
            cout << result[i] << " ";
        cout << result[n - 1];
    } else 
        cout << -1 << endl;

    return 0;
}
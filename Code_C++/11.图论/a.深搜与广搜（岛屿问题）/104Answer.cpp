#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
using namespace std;

int n, m;
int count;

int dir[4][2] = {0, 1, 1, 0, 0, -1, -1, 0};
void dfs(vector<vector<int>>& imap, vector<vector<bool>>& visited, int x, int y, int mark){
    // 终止条件：访问过的节点 或者 遇到海水
    if(visited[x][y] || imap[x][y] == 0)
        return;
    visited[x][y] = true;
    imap[x][y] = mark;
    count++;
    for (int i = 0; i < 4; i++) {
        int nextx = x + dir[i][0];
        int nexty = y + dir[i][1];
        if (nextx < 0 || nextx >= n || nexty < 0 || nexty >= m) 
            continue;
        dfs(imap, visited, nextx, nexty, mark);
    }
}

int main(){
    cin >> n >> m;

    vector<vector<int>> imap(n, vector<int>(m, 0));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> imap[i][j];
        }
    }

    vector<vector<bool>> visited(n, vector<bool>(m, false)); // 标记访问过的点
    unordered_map<int, int> imapNum;    // 用map来记录岛屿编号和对应的面积
    int mark = 2;   // 记录每个岛屿的编号
    bool isAllGrid = true;  // 标记是否整个地图都是陆地
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(imap[i][j] == 0)
                isAllGrid = false;
            if(!visited[i][j] && imap[i][j] == 1){
                count = 0;  // 初始化岛屿面积为0
                dfs(imap, visited, i, j, mark);
                imapNum[mark] = count;  // 记录岛屿面积
                mark++;
            }
        }
    }

    // 如果都是陆地，返回全面积
    if (isAllGrid) {
        cout << n * m << endl;
        return 0;
    }

    int result = 0; // 记录最终结果
    unordered_set<int> visitedMap; // 标记访问过的岛屿
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            count = 1;
            visitedMap.clear(); // 每次使用时，清空
            if(imap[i][j] == 0){
                for (int k = 0; k < 4; k++) {
                    int neari = i + dir[k][0];
                    int nearj = j + dir[k][1];
                    if (neari < 0 || neari >= n || nearj < 0 || nearj >= m)
                        continue;
                    if (visitedMap.count(imap[neari][nearj])) 
                        continue;
                    // 把相邻四面的岛屿数量加起来
                    count += imapNum[imap[neari][nearj]];
                    visitedMap.insert(imap[neari][nearj]);
                }
            }
            result = max(result, count);
        }
    }
    cout << result << endl;

    return 0;
}
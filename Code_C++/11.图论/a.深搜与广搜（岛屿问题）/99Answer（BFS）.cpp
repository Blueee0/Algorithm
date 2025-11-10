#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int dir[4][2] = {0, 1, 1, 0, 0, -1, -1, 0};
void bfs(const vector<vector<int>> &imap,vector<vector<bool>> &visited,int x,int y){
    queue<pair<int, int>> que;
    que.push({x, y});
    visited[x][y] = true;

    while(!que.empty()){
        pair<int, int> cur = que.front();
        que.pop();

        int curx = cur.first;
        int cury = cur.second;
        for(int i = 0; i < 4; i++){
            int nextx = curx + dir[i][0];
            int nexty = cury + dir[i][1];
            if (nextx < 0 || nextx >= imap.size() || nexty < 0 || nexty >= imap[0].size()) 
                continue;
            if (!visited[nextx][nexty] && imap[nextx][nexty] == 1) {
                que.push({nextx, nexty});
                visited[nextx][nexty] = true;
            }
        }
    }
}


int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> imap(n, (vector<int>(m, 0)));
    vector<vector<bool>> visited(n, (vector<bool>(m, false)));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> imap[i][j];
        }
    }

    int result = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (imap[i][j] == 1 && visited[i][j] == false) {
                result++;
                bfs(imap, visited, i, j);
            }
        }
    }

    cout << result << endl;
    return 0;
}
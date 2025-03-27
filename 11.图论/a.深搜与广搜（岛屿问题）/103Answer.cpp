#include <iostream>
#include <vector>
using namespace std;

int n, m;
int dir[4][2] = {0,1,1,0,0,-1,-1,0};
void dfs(vector<vector<int>>& imap, vector<vector<bool>>& visited, int x, int y){
    if (visited[x][y]) 
        return;

    visited[x][y] = true;
    for(int i = 0; i < 4; i++){
        int nextx = x + dir[i][0];
        int nexty = y + dir[i][1];
        if(nextx < 0|| nextx >= n|| nexty < 0|| nexty >= m)
            continue;
        if (imap[x][y] > imap[nextx][nexty])    // 注意：这里是从低向高遍历
            continue;
        dfs(imap, visited, nextx, nexty);
    }
}

int main(){
    cin >> n >> m;

    vector<vector<int>> imap(n,vector<int>(m,0));

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> imap[i][j];
        }
    }

    // 标记从第一组边界上的节点出发，可以遍历的节点
    vector<vector<bool>> firstBorder(n, vector<bool>(m, false));

    // 标记从第一组边界上的节点出发，可以遍历的节点
    vector<vector<bool>> secondBorder(n, vector<bool>(m, false));

    // 从左边和右边 向中间遍历
    for (int j = 0; j < m; j++) {
        dfs (imap, firstBorder, 0, j);      // 遍历最上行，接触第一组边界
        dfs (imap, secondBorder, n - 1, j); // 遍历最下行，接触第二组边界
    }
    
    // 从上边和下边，向中间遍历
    for (int i = 0; i < n; i++) {
        dfs (imap, firstBorder, i, 0);      // 遍历最左列，接触第一组边界
        dfs (imap, secondBorder, i, m - 1); // 遍历最右列，接触第二组边界
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (firstBorder[i][j] && secondBorder[i][j]) 
                cout << i << " " << j << endl;
        }
    }

    return 0;
}
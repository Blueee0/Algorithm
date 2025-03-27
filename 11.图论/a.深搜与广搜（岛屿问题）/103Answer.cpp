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
        if (imap[x][y] > imap[nextx][nexty])    // ע�⣺�����Ǵӵ���߱���
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

    // ��Ǵӵ�һ��߽��ϵĽڵ���������Ա����Ľڵ�
    vector<vector<bool>> firstBorder(n, vector<bool>(m, false));

    // ��Ǵӵ�һ��߽��ϵĽڵ���������Ա����Ľڵ�
    vector<vector<bool>> secondBorder(n, vector<bool>(m, false));

    // ����ߺ��ұ� ���м����
    for (int j = 0; j < m; j++) {
        dfs (imap, firstBorder, 0, j);      // ���������У��Ӵ���һ��߽�
        dfs (imap, secondBorder, n - 1, j); // ���������У��Ӵ��ڶ���߽�
    }
    
    // ���ϱߺ��±ߣ����м����
    for (int i = 0; i < n; i++) {
        dfs (imap, firstBorder, i, 0);      // ���������У��Ӵ���һ��߽�
        dfs (imap, secondBorder, i, m - 1); // ���������У��Ӵ��ڶ���߽�
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (firstBorder[i][j] && secondBorder[i][j]) 
                cout << i << " " << j << endl;
        }
    }

    return 0;
}
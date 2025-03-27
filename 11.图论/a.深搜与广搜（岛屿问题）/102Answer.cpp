#include <iostream>
#include <vector>
using namespace std;

int dir[4][2] = {0,1,1,0,0,-1,-1,0};
void dfs(vector<vector<int>>& imap, int x, int y){
    imap[x][y] = 2;
    for(int i = 0; i < 4; i++){
        int nextx = x + dir[i][0];
        int nexty = y + dir[i][1];
        if(nextx < 0|| nextx >= imap.size()|| nexty < 0|| nexty >= imap[0].size())
            continue;
        if (imap[nextx][nexty] == 0 || imap[nextx][nexty] == 2) 
            continue;
        dfs(imap, nextx, nexty);
    }
}

int main(){
    int n, m;
    cin >> n >> m;

    vector<vector<int>> imap(n,vector<int>(m,0));

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> imap[i][j];
        }
    }

    // ����ߺ��ұ� ���м����
    for (int i = 0; i < n; i++) {
        if (imap[i][0] == 1) 
            dfs(imap, i, 0);
        if (imap[i][m - 1] == 1) 
            dfs(imap, i, m - 1);
    }
    
    // ���ϱߺ��±ߣ����м����
    for (int j = 0; j < m; j++) {
        if (imap[0][j] == 1) 
            dfs(imap, 0, j);
        if (imap[n - 1][j] == 1) 
            dfs(imap, n - 1, j);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (imap[i][j] == 1) 
                imap[i][j] = 0;
            if (imap[i][j] == 2) 
                imap[i][j] = 1;
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cout << imap[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
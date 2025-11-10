#include <iostream>
#include <vector>
using namespace std;

int cnt;
int dir[4][2] = {0,1,1,0,0,-1,-1,0};
void dfs(const vector<vector<int>>& imap, vector<vector<bool>>& visited, int x, int y){
    for(int i = 0; i < 4; i++){
        int nextx = x + dir[i][0];
        int nexty = y + dir[i][1];
        if(nextx < 0|| nextx >= imap.size()|| nexty < 0|| nexty >= imap[0].size()){
            continue;
        }
        if(!visited[nextx][nexty] && imap[nextx][nexty] == 1){
            cnt++;
            visited[nextx][nexty] = true;
            dfs(imap, visited, nextx, nexty);
        }
    }
}

int main(){
    int n, m;
    cin >> n >> m;
    vector<vector<int>> imap(n,vector<int>(m,0));
    vector<vector<bool>> visited(n,vector<bool>(m,0));

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> imap[i][j];
        }
    }

    int result = 0; 
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(!visited[i][j] && imap[i][j] == 1){
                cnt = 1;
                visited[i][j] = true;
                dfs(imap, visited, i, j);
                result = max(result, count);
            }
        }
    }
    cout << result << endl;
    return 0;
}
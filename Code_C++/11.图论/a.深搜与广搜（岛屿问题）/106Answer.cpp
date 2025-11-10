#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n, m;
    cin >> n >> m;

    vector<vector<int>> imap(n, vector<int>(m, 0));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> imap[i][j];
        }
    }

    int dir[4][2] = {0, 1, 1, 0, 0, -1, -1, 0};
    int result = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(imap[i][j] == 1){
                for(int k = 0; k < 4; k++){
                    int nexti = i + dir[k][0];
                    int nextj = j + dir[k][1];
                    if(nexti < 0 || nexti >= n || nextj < 0 || nextj >= m){
                        result++;
                        continue;
                    }
                    if(imap[nexti][nextj] == 0){
                        result++;
                    }
                }
            }
        }
    }

    cout << result << endl;

    return 0;
}
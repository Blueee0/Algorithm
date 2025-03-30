#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
using namespace std;

int n, m;
int count;

int dir[4][2] = {0, 1, 1, 0, 0, -1, -1, 0};
void dfs(vector<vector<int>>& imap, vector<vector<bool>>& visited, int x, int y, int mark){
    // ��ֹ���������ʹ��Ľڵ� ���� ������ˮ
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

    vector<vector<bool>> visited(n, vector<bool>(m, false)); // ��Ƿ��ʹ��ĵ�
    unordered_map<int, int> imapNum;    // ��map����¼�����źͶ�Ӧ�����
    int mark = 2;   // ��¼ÿ������ı��
    bool isAllGrid = true;  // ����Ƿ�������ͼ����½��
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(imap[i][j] == 0)
                isAllGrid = false;
            if(!visited[i][j] && imap[i][j] == 1){
                count = 0;  // ��ʼ���������Ϊ0
                dfs(imap, visited, i, j, mark);
                imapNum[mark] = count;  // ��¼�������
                mark++;
            }
        }
    }

    // �������½�أ�����ȫ���
    if (isAllGrid) {
        cout << n * m << endl;
        return 0;
    }

    int result = 0; // ��¼���ս��
    unordered_set<int> visitedMap; // ��Ƿ��ʹ��ĵ���
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            count = 1;
            visitedMap.clear(); // ÿ��ʹ��ʱ�����
            if(imap[i][j] == 0){
                for (int k = 0; k < 4; k++) {
                    int neari = i + dir[k][0];
                    int nearj = j + dir[k][1];
                    if (neari < 0 || neari >= n || nearj < 0 || nearj >= m)
                        continue;
                    if (visitedMap.count(imap[neari][nearj])) 
                        continue;
                    // ����������ĵ�������������
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
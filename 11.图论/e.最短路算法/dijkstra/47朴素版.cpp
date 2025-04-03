#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main(){

    int n, m, s, e, val;
    cin >> n >> m;
    vector<vector<int>> grid(n + 1, vector<int>(n + 1, INT_MAX));
    while(m--){
        cin >> s >> e >> val;
        grid[s][e] = val;
    }
    int start = 1, end = n;
    
    // ��¼�Ƿ��ʽڵ㵽Դ��ľ���
    vector<int> minDist(n + 1, INT_MAX);
    minDist[start] = 0;

    // ��¼���ʹ��Ľڵ�
    vector<bool> visited(n + 1, false);
    
    // �������нڵ�
    for(int i = 1; i <= n; i++){
        // ��һ����ѡԴ�㵽�ĸ��ڵ���Ҹýڵ�δ�����ʹ�
        int minVal = INT_MAX;
        int cur = 1;
        for (int j = 1; j <= n; j++){
            if(!visited[j] && minDist[j] < minVal){
                minVal = minDist[j];
                cur = j;
            }
        }

        // �ڶ�����������ڵ㱻��Ƿ��ʹ�
        visited[cur] = true;


        // �����������·Ƿ��ʽڵ㵽Դ��ľ��루������minDist���飩
        for(int j = 1; j <= n; j++){
            if(!visited[j] && grid[cur][j] != INT_MAX && minDist[cur] + grid[cur][j] < minDist[j]){
                minDist[j] = minDist[cur] + grid[cur][j];
            }
        }
    }
    if (minDist[end] == INT_MAX)    // ���ܵ����յ�
        cout << -1 << endl; 
    else 
        cout << minDist[end] << endl; // �����յ����·��


    return 0;
}
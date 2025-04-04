#include <iostream>
#include <vector>
#include <list>
#include <climits>
using namespace std;

int main(){
    int n, m, s, t, val, src, dst, k;
    cin >> n >> m;
    vector<vector<int>> umap; 
    for(int i = 0; i < m; i++){
        cin >> s >> t >> val;
        umap.push_back({s, t, val});
    }
    cin >> src >> dst >> k;

    vector<int> minDist(n + 1, INT_MAX);
    vector<int> minDist_copy(n + 1, INT_MAX);
    minDist[src] = 0;
    for(int i = 0; i < k + 1; i++){
        minDist_copy = minDist;
        for(vector<int> &side : umap){
            int from = side[0];
            int to = side[1];
            int value = side[2];
            // minDist[from] != INT_MAX ��ֹ��δ������Ľڵ����
            if(minDist_copy[from] != INT_MAX && minDist[to] > minDist_copy[from] + value){
                minDist[to] = minDist_copy[from] + value;
            }
        }
    }

    if (minDist[dst] == INT_MAX) 
        cout << "unreachable" << endl; // ���ܵ����յ�
    else 
        cout << minDist[dst] << endl; // �����յ����·������
}
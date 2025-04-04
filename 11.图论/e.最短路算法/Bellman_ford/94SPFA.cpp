#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <climits>
using namespace std;

struct Edge { // �ڽӱ�
    int to;   // ���ӵĽڵ�
    int val;  // �ߵ�Ȩ��

    Edge(int t, int w): to(t), val(w) {}  // ���캯��
};

int main(){
    int n, m, s, t, val;
    cin >> n >> m;
    vector<list<Edge>> umap(n + 1);
    vector<bool> isInQueue(n + 1);

    for(int i = 0; i < m; i++){
        cin >> s >> t >> val;
        umap[s].push_back(Edge(t, val));
    }

    int start = 1, end = n;
    vector<int> minDist(n + 1, INT_MAX);
    minDist[start] = 0;

    queue<int> que;
    que.push(start);

    while(!que.empty()){
        int node = que.front(); que.pop();
        isInQueue[node] = false;
        for(Edge edge : umap[node]){
            int from = node;
            int to = edge.to;
            int value = edge.val;
            if (minDist[to] > minDist[from] + value) {
                minDist[to] = minDist[from] + value; 
                // �Ѿ��ڶ������Ԫ�ز����ظ����
                if (isInQueue[to] == false) { 
                    que.push(to);
                    isInQueue[to] = true;
                }
            }
        }
    }


    if (minDist[end] == INT_MAX) 
        cout << "unconnected" << endl; // ���ܵ����յ�
    else 
        cout << minDist[end] << endl; // �����յ����·������
}